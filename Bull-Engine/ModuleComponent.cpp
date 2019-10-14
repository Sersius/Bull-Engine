#include "ModuleComponent.h"

ModuleComponent::ModuleComponent()
{

}

ModuleComponent::~ModuleComponent()
{

}

void ModuleComponent::Update(float dt)
{

}

void ModuleComponent::SetEnable(bool set)
{
	active = set;
}

bool ModuleComponent::GetEnabled()
{
	return active;
}