#include "Application.h"
#include "SerializationScene.h"
#include "Mesh.h"
#include "ModuleUI.h"
#include "InspectorWindow.h"



SerializationScene::SerializationScene() 
{}

SerializationScene::~SerializationScene()
{

}

bool SerializationScene::SaveScene(const char* scene_name)
{
	bool ret = false;
	JSON_Value* json_value = json_value_init_array();
	JSON_Array* json_array = json_value_get_array(json_value);

	ret = SaveGameObjects(json_array);
	if(ret == true)
	{
		std::string extension = ".json";
		std::string final_name = scene_name + extension;
	
		final_path = (destination + final_name).c_str();
		json_serialize_to_file_pretty(json_value, final_path.c_str());

		LOG("Scene saved correctly!");
		LOG("Saved in: %s", final_path.c_str());
		
		return ret;
	}
	else
	{
		LOG("Error saving scene")
		return ret;
	}
		
}


bool SerializationScene::SaveGameObjects(JSON_Array* json_array) const
{
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin(); iterator != App->scene_intro->GameObjects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator),json_array);
	}
	return true;
}

void SerializationScene::LoadScene(const char* name_scene)
{
	App->scene_intro->UnselectGameObject();
	App->scene_intro->root->DeleteScene();
	App->audio->audios.clear();
	std::string extension;
	extension = name_scene;
	uint type = extension.find_last_of(".");
	if (type != std::string::npos)
		extension = extension.substr(type);

	std::string final_name;
	std::string aux_extension = ".json";

	if(extension == aux_extension)
		final_name = name_scene;
	else
		final_name = name_scene + aux_extension;

	final_path = destination + final_name;
	JSON_Value* scene = json_parse_file(final_path.c_str());
	JSON_Array* Array = json_value_get_array(scene);
	JSON_Object* obj = nullptr;
	
	App->scene_intro->root = App->scene_intro->CreateGameObject(nullptr);
	App->scene_intro->root->SetName("Root");

	int size = json_array_get_count(Array);

	for (int i = 0; i < size; i++)
	{
		obj = json_array_get_object(Array, i);
		GameObject* go = App->scene_intro->CreateGameObject(App->scene_intro->root);
		go->LoadInfoGambeObject(obj,go);
		//App->scene_intro->root->children.clear();
	}

	for (std::vector<GameObject*>::iterator iterator = App->scene_intro->GameObjects.begin(); iterator != App->scene_intro->GameObjects.end(); ++iterator) {

		GetHierarchy((*iterator));
		if ((*iterator)->name.compare("Root") == false)
		{
			App->scene_intro->root = (*iterator);
		}
	}

	for (std::vector<GameObject*>::iterator iterator = App->scene_intro->GameObjects.begin() + 1; iterator != App->scene_intro->GameObjects.end(); ++iterator) {

		if ((*iterator)->name.compare("Camera") == false) {
			App->scene_intro->camera_scene = (*iterator);
		}

	}
	LOG("%s loaded correctly",name_scene);
}

void SerializationScene::GetHierarchy(GameObject* go) const
{	
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() +1 ; iterator != App->scene_intro->GameObjects.end(); ++iterator)
	{
		if ((*iterator)->uuid_parent == go->uuid)
		{
			(*iterator)->parent = go;
			go->children.push_back((*iterator));
		}
	}	
}