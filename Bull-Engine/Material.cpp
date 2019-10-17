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
	if (App->loadFBX->LoadTexture(texture_path) == true)
	{
		this->texture_path = texture_path;
	}
}