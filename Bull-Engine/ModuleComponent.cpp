#include "ModuleComponent.h"

Component::Component()
{

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