#include "ModuleComponent.h"

Component::Component(GameObject* parent, COMPONENT_TYPE type) : parent(parent)
{
	this->parent = parent;
	this->type = type;
}

Component::~Component()
{

}

void Component::Update(float dt)
{

}

void Component::SetEnable(bool set)
{
	active = set;
}

bool Component::GetEnabled()
{
	return active;
}