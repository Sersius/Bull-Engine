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
	App->loadFBX->LoadTexture(texture_path,id);
	this->texture_path = texture_path;
	
}

void Material::SaveMaterial(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);
	json_object_set_number(componentObj, "Type:", this->type);
	if(this->texture_path ==nullptr)
	json_object_set_string(componentObj, "texture_path",texture_path);

	json_array_append_value(componentsObj, component);
}

void Material::LoadTexture(JSON_Object* obj, GameObject* go)
{
	json_object_get_number(obj, "Type:");
	go->material->texture_path = json_object_get_string(obj, "texture_path");
	if (go->material->texture_path != nullptr)
		GetTexture((char*)texture_path);
}