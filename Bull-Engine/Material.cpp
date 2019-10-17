#include "Material.h"
#include "ModuleLoadFBX.h"
#include "Application.h"

Material::Material(GameObject* parent) : Component(parent, COMPONENT_TYPE::MATERIAL)
{

}

Material::~Material()
{

}

void Material::Update(float dt)
{

}

void Material::GetTexture(char* texture_path)
{
	App->loadFBX->LoadTexture(texture_path);
	this->texture_path = texture_path;
	
}