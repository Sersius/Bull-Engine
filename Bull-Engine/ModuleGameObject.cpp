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
	/*else if (type == COMPONENT_TYPE::TRANSFORM)
	{
		transform = new Transform(this);
		_type = transform;
	}*/
	return _type;
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
	if (ImGui::TreeNodeEx(name_str))
	{
		if (children.size() != 0) {
			uint size = children.size();
			for (uint k = 0; k < size; k++)
			{
				children[k]->BlitHierarchy();
			}
		}
		ImGui::TreePop();
	}
	
}
