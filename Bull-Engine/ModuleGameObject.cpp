#include "Application.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"

#include "ModuleGameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"

#include "ImGui/imgui.h"

GameObject::GameObject(GameObject* parent)
{
	
	this->parent = parent;
	if (parent != nullptr)
		parent->children.push_back(this);

	CreateComponent(COMPONENT_TYPE::TRANSFORM);
}

GameObject::~GameObject()
{

}

void GameObject::Update(float dt)
{

}

Component* GameObject::CreateComponent(COMPONENT_TYPE type,char* name)
{
	Component* _type = nullptr;
	if (type == COMPONENT_TYPE::MATERIAL)
	{
		material = new Material(this);
		_type = material;
	}
	else if (type == COMPONENT_TYPE::MESH)
	{
		mesh = new Mesh(this,name);
		_type = mesh;
	}
	else if (type == COMPONENT_TYPE::TRANSFORM)
	{
		transform = new Transform(this);
		_type = (Component*)transform;
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
	Mesh* mesh_box = (Mesh*)GetComponentMesh();

	if (mesh_box != nullptr)
	{
		bounding_box.SetNegativeInfinity();
		bounding_box.Enclose((float3*)mesh_box->info_mesh.vertex, mesh_box->info_mesh.num_vertex / 3);

		OBB obb(bounding_box);
		
		Transform* transform_box = (Transform*)GetComponentTransform();

		obb.Transform(transform_box->GetMatrix());

		bounding_box = obb.MinimalEnclosingAABB();
	}
}