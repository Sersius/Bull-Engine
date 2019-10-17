#include "ModuleGameObject.h"
#include "Material.h"
#include "Mesh.h"
#include "ImGui/imgui.h"
GameObject::GameObject(GameObject* parent)
{
	
	this->parent = parent;
}

GameObject::~GameObject()
{

}

void GameObject::Update(float dt)
{

}

Component* GameObject::CreateComponent(COMPONENT_TYPE type,char* name)
{
	if (type == COMPONENT_TYPE::MATERIAL)
	{
		material = new Material(this);
	}
	else if (type == COMPONENT_TYPE::MESH)
	{
		mesh = new Mesh(this,name);
	}
	return material;
}

Component* GameObject::GetComponent(COMPONENT_TYPE type, std::string name)
{
	return nullptr;
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

void GameObject::BlitHierarchy()
{
	char name_str[250];
	sprintf_s(name_str, 250, "%s##%i", name.c_str());
	if(ImGui::TreeNodeEx(name_str))
	ImGui::TreePop();
}
