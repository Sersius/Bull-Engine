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

void Material::GetTexture(std::string texture_path)
{
	std::string destination = "Library/Textures/";
	int fileExtPos = texture_path.find_last_of(".");
	if (fileExtPos <= 15)
		texture_path = texture_path.substr(0, fileExtPos);
	else {
		texture_path = texture_path.substr(texture_path.find_last_of("\\") + 1);
		std::string::size_type const p(texture_path.find_last_of('.'));
		 texture_path = texture_path.substr(0, p);
	}
	/*if (file_ >= 0)
		texture_path = texture_path.s(0, file_);*/
	std::string new_extension = ".dds";
	std::string final_path_texture = (texture_path + new_extension).c_str();
	std::string final_path = (destination + final_path_texture).c_str();
	App->loadFBX->LoadTexture(final_path.c_str(),id);
	this->texture_path = texture_path.c_str();
	
}

void Material::SaveMaterial(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);
	json_object_set_number(componentObj, "Type:", this->type);
	if(texture_path.compare("") != false)
	json_object_set_string(componentObj, "texture_path",texture_path.c_str());

	json_array_append_value(componentsObj, component);
}

void Material::LoadTexture(JSON_Object* obj, GameObject* go)
{
	json_object_get_number(obj, "Type:");
	go->material->texture_path = json_object_get_string(obj, "texture_path");
	if (go->material->texture_path.compare("") != false)
		GetTexture((char*)texture_path.c_str());
	
}