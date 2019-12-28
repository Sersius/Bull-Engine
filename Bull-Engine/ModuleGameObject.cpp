#include "Application.h"
#include "ModuleInput.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"

#include "ModuleGameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"
#include "AudioEmitter.h"
#include "AudioListener.h"
#include "ReverbZone.h"

#include "ImGui/imgui.h"

GameObject::GameObject(GameObject* parent)
{
	
	this->parent = parent;
	if (parent != nullptr)
		parent->children.push_back(this);

	uuid = App->GenRandomNumber();
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

		if (children[i]->reverb_zone != nullptr)
			DrawBoundingBox();
	}
	App->scene_intro->GameObjects.size();
	if (camera)
		camera->Update(dt);
	if (audio_emitter)
		audio_emitter->Update(dt);
	if (reverb_zone)
		reverb_zone->Update(dt);
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
	else if (type == COMPONENT_TYPE::AUDIO_EMITTER)
	{
		audio_emitter = new AudioEmitter(this);
		_type = (Component*)audio_emitter;
		components.push_back(audio_emitter);
	}
	else if (type == COMPONENT_TYPE::AUDIO_LISTENER)
	{
		audio_listener = new AudioListener(this);
		_type = (Component*)audio_listener;
		components.push_back(audio_listener);
	}
	else if (type == COMPONENT_TYPE::REVERB_ZONE)
	{
		reverb_zone = new ReverbZone(this);
		_type = (Component*)reverb_zone;
		components.push_back(reverb_zone);
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

AudioEmitter * GameObject::GetComponentAudioEmitter() const
{
	return (AudioEmitter*)GetComponent(COMPONENT_TYPE::AUDIO_EMITTER);
}

AudioListener * GameObject::GetComponentAudioListener() const
{
	return (AudioListener*)GetComponent(COMPONENT_TYPE::AUDIO_LISTENER);
}

ReverbZone * GameObject::GetComponentReverbZone() const
{
	return (ReverbZone*)GetComponent(COMPONENT_TYPE::REVERB_ZONE);
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

	if (root == App->scene_intro->selected)
		flag |= ImGuiTreeNodeFlags_Selected;

	if (ImGui::TreeNodeEx(name_str,flag))
	{
		if (ImGui::IsItemHovered())
		{
			if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN)
			{
				App->scene_intro->SetSelectedGameObject(root);
			}
		}
		for (std::vector<GameObject*>::iterator children = root->children.begin(); children != root->children.end(); ++children)
		{
			ImGui::PushID(*children);
			BlitHierarchy(*children);
			ImGui::PopID();
		}		
		
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

	if (GetComponentMesh() == nullptr && children.size() <= 0)
	{
		Transform* transform = GetComponentTransform();
		OBB boundingBox(aux_box);
		boundingBox.Transform(transform->GetGlobalMatrix());

		aux_box = boundingBox.MinimalEnclosingAABB();
	}
	else if (GetComponentMesh() != nullptr)
		aux_box = parent->bounding_box;

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
	JSON_Array* componentsGO = json_value_get_array(components);

	if (go->transform != nullptr)
		go->transform->SaveTransform(componentsGO);
	if (go->mesh != nullptr)
		go->mesh->SaveMesh(componentsGO);
	if (go->material != nullptr && go->material->texture_path.empty() == false)
		go->material->SaveMaterial(componentsGO);
	if (go->camera != nullptr)
		go->camera->SaveCamera(componentsGO);
	if (go->audio_listener != nullptr)
		go->audio_listener->SaveListener(componentsGO);
	if (go->audio_emitter != nullptr)
		go->audio_emitter->SaveEmitter(componentsGO);

	json_object_set_value(object_json, "Components:", components);
	json_array_append_value(json_array, value_json);
}

void GameObject::LoadInfoGambeObject(JSON_Object* obj,GameObject* go)
{
	//BASIC INFO
	go->SetName(json_object_get_string(obj, "Name:"));
	go->uuid = json_object_get_number(obj, "UUID:");
	go->uuid_parent = json_object_get_number(obj, "Parent UUID:");

	//COMPONENTS INFO
	JSON_Array* Array = json_object_get_array(obj, "Components:");
	JSON_Object* type;
	int size = json_array_get_count(Array);

	for (int i = 0; i < size; i++)
	{
		type = json_array_get_object(Array, i);
		int num_type = json_object_get_number(type, "Type:");
		if (num_type == 1) {
			go->transform->LoadTransform(type);
		}
		else if (num_type == 2)
		{
			go->CreateComponent(COMPONENT_TYPE::MESH);
			go->mesh->LoadMesh(type,go);
		}
		else if (num_type == 3)
		{
			CreateComponent(COMPONENT_TYPE::MATERIAL);
			go->material->LoadTexture(type, go);
		}
		else if (num_type == 4)
		{
			CreateComponent(COMPONENT_TYPE::CAMERA);
			go->camera->LoadCamera(type, go);
		}
		else if (num_type == 6)
		{
			CreateComponent(COMPONENT_TYPE::AUDIO_LISTENER);

		}
		else if (num_type == 5)
		{
			CreateComponent(COMPONENT_TYPE::AUDIO_EMITTER);
			go->audio_emitter->LoadEmitter(type, go);
		}
	}

}

void GameObject::DeleteScene()
{
	App->scene_intro->camera_scene = nullptr;
	App->scene_intro->GameObjects.clear();
	App->renderer3D->meshes.clear();
	components.clear();
	children.clear();
}

void GameObject::MoveGO()
{
	/*math::float3 curr_pos = parent->GetComponentTransform()->position;
	
	float x = 0.0f;
	float y = 0.0f;
	float z = 0.0f;
	if (parent->GetComponentTransform()->position.x <= 10) {
		math::float3 move = math::float3(parent->GetComponentTransform()->position.x += 0.1f, y, z);
		parent->GetComponentTransform()->SetPosition(move);

	}
	if (parent->GetComponentTransform()->position.x == 10) {
		go_right = false;
		go_left = true;

	}
	else if (go_left == true)
	{
		math::float3 move = math::float3(parent->GetComponentTransform()->position.x -= 0.1f, y, z);
		parent->GetComponentTransform()->SetPosition(move);
	}*/

	/*if (go_right == true)
	{
		if(parent->GetComponentTransform()->position.x<10){}
		parent->GetComponentTransform()->position.x += 0.1f;
		
		move += curr_pos;
		parent->GetComponentTransform()->SetPosition(move);
		go_right = false;
		go_left = true;
	}*/
	/*else if (parent->GetComponentTransform()->position.x > -10 && go_left ==true)
	{
		parent->GetComponentTransform()->position.x += 0.1f;
		math::float3 move = math::float3(parent->GetComponentTransform()->position.x -= 0.1f, y, z);
		move += curr_pos;
		parent->GetComponentTransform()->SetPosition(move);
		go_right = true;
		go_left = false;
	}*/
	/*if (going_a == true) {
		if (curr_pos.x < pos_a.x) {
			x += velocity * dt;
		}
		else {
			going_a = false;
			going_b = true;
		}
	}
	else {
		if (curr_pos.x > pos_b.x) {
			x -= velocity * dt;
		}
		else {
			going_a = true;
			going_b = false;
		}
	}*/

	
	
}