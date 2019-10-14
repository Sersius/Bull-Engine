#include "ModuleGameObject.h"

ModuleGameObject::ModuleGameObject(std::string name, ModuleGameObject* parent)
{
	this->name = name;
	this->parent = parent;
}

ModuleGameObject::~ModuleGameObject()
{

}

void ModuleGameObject::Update(float dt)
{

}

ModuleComponent* ModuleGameObject::CreateComponent(COMPONENT_TYPE type, std::string name)
{
	return nullptr;
}

ModuleComponent* ModuleGameObject::GetComponent(COMPONENT_TYPE type, std::string name)
{
	return nullptr;
}