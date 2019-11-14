#include "Application.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"

#include "ModuleGameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

#include "ImGui/imgui.h"
#include <random>

GameObject::GameObject(GameObject* parent)
{
	
	this->parent = parent;
	if (parent != nullptr)
		parent->children.push_back(this);

	uuid = GenRandomNumber();
	CreateComponent(COMPONENT_TYPE::TRANSFORM);
	if(App!=nullptr)
	App->scene_intro->GameObjects.push_back(this);
}

GameObject::~GameObject()
{

}

void GameObject::Update(float dt)
{
	for (uint i = 0; i < children.size(); i++) {
		children[i]->Update(dt);
	}
	App->scene_intro->GameObjects.size();
	if (camera)
		camera->Update(dt);

	DrawBoundingBox();
}

Component* GameObject::CreateComponent(COMPONENT_TYPE type,char* name)
{
	Component* _type = nullptr;
	if (type == COMPONENT_TYPE::MATERIAL)
	{
		material = new Material(this);
		_type = material;
		components.push_back(material);
	}
	else if (type == COMPONENT_TYPE::MESH)
	{
		mesh = new Mesh(this,name);
		_type = mesh;
		components.push_back(mesh);
	}
	else if (type == COMPONENT_TYPE::TRANSFORM)
	{
		transform = new Transform(this);
		_type = (Component*)transform;
		components.push_back((Component*)transform);
	}
	else if (type == COMPONENT_TYPE::CAMERA)
	{
		camera = new Camera(this);
		_type = (Component*)camera;
		components.push_back(camera);
	}
	return _type;
}

Material* GameObject::GetComponentMaterial() const
{
	return (Material*)GetComponent(COMPONENT_TYPE::MATERIAL);
}

Mesh * GameObject::GetComponentMesh() const
{
	return (Mesh*)GetComponent(COMPONENT_TYPE::MESH);
}

Transform * GameObject::GetComponentTransform() const
{
	return (Transform*)GetComponent(COMPONENT_TYPE::TRANSFORM);
}

Camera * GameObject::GetComponentCamera() const
{
	return (Camera*)GetComponent(COMPONENT_TYPE::CAMERA);
}

Component * GameObject::GetComponent(COMPONENT_TYPE type) const
{
	Component* component = nullptr;

	for (auto item = components.begin(); item != components.end(); item++)
	{
		if ((*item)->type == type)
		{
			component = (*item);
			return component;
		}
	}

	return component;
}

void GameObject::SetName(const char* name)
{
	this->name = name;
	//LOG("name: %s", name);
}

void GameObject::SetActive(bool active)
{
	this->active = active;
}

const char* GameObject::GetName()const
{
	return name.c_str();
}

void GameObject::BlitHierarchy(GameObject* root)
{
	ImGuiTreeNodeFlags flag = 0;
	if (root->children.empty())
		flag += ImGuiTreeNodeFlags_::ImGuiTreeNodeFlags_Leaf;
	char name_str[250];
	sprintf_s(name_str, 250, "%s##%i", root->name.c_str());
	if (ImGui::TreeNodeEx(name_str,flag))
	{
		if (ImGui::IsItemHovered())
		{
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				App->scene_intro->SetSelectedGameObject(root);
			}
		}
		//if (ImGui::IsItemClicked())
		//{
		//	App->scene_intro->SetSelectedGameObject(root);
		//	//App->scene_intro->SetSelectedGameObject(root);
		//}
		for (std::vector<GameObject*>::iterator children = root->children.begin(); children != root->children.end(); ++children)
		{
			ImGui::PushID(*children);
			BlitHierarchy(*children);
			ImGui::PopID();
		}
		//if (children.size() != 0) {
		//	uint size = children.size();
		//	/*for (uint k = 0; k < size; k++)
		//	{
		//		children[k]->BlitHierarchy(root);
		//	}*/
		//}
		
		
		ImGui::TreePop();
	}
	
	
}

void GameObject::BoundingBox()
{
	bounding_box.SetNegativeInfinity();

	if (mesh != nullptr && transform != nullptr)
	{
		bounding_box.Enclose((float3*)mesh->info_mesh.vertex, mesh->info_mesh.num_vertex);
	
		obb.SetFrom(bounding_box);
		obb.Transform(transform->GetGlobalMatrix());

		if(obb.IsFinite())
			bounding_box = obb.MinimalEnclosingAABB();
	}

	for (uint i = 0; i < children.size(); ++i) {
		children[i]->BoundingBox();
	}	
}

math::AABB GameObject::GetAABB()
{
	math::AABB aux_box(float3(0, 0, 0), float3(0, 0, 0));

	aux_box = App->scene_intro->selected->bounding_box;

	return aux_box;
}

void GameObject::DrawBoundingBox()
{
	glBegin(GL_LINES);
	glColor4f(1.0f, 1.0f, 0.0f, 1.0f);

	for (uint i = 0; i < bounding_box.NumEdges(); i++)
	{
		glVertex3f(bounding_box.Edge(i).a.x, bounding_box.Edge(i).a.y, bounding_box.Edge(i).a.z);
		glVertex3f(bounding_box.Edge(i).b.x, bounding_box.Edge(i).b.y, bounding_box.Edge(i).b.z);
	}
	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

	for (uint i = 0; i < children.size(); ++i)
	{
		children[i]->DrawBoundingBox();
	}
}

void GameObject::SaveInfoGameObject(GameObject* go,JSON_Array* json_array)
{
	//BASIC INFO
	JSON_Value* value_json = json_value_init_object();
	JSON_Object* object_json = json_value_get_object(value_json);
	
	json_object_set_string(object_json, "Name:", go->name.c_str());
	json_object_set_number(object_json, "UUID:", go->uuid);
	if(go->parent!=nullptr)
		json_object_set_number(object_json, "Parent UUID:", go->parent->uuid);

	//COMPONENTS INFO
	JSON_Value* components = json_value_init_array();
	JSON_Array* componentsObj = json_value_get_array(components);

	if (go->transform != nullptr)
		go->transform->SaveTransform(componentsObj);

	json_object_set_value(object_json, "Components:", components);

	json_array_append_value(json_array, value_json);
}

uint GameObject::GenRandomNumber()
{
	uint number = 0;
	std::random_device rd;
	std::mt19937_64 eng(rd());
	std::uniform_int_distribution<uint> distr;
	number = distr(eng);

	return number;
}
