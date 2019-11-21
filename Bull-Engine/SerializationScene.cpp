#include "Application.h"
#include "SerializationScene.h"
#include "Mesh.h"



SerializationScene::SerializationScene() 
{}

SerializationScene::~SerializationScene()
{

}

//void SerializationScene::Update(float dt)
//{
//
//}

bool SerializationScene::SaveScene(const char* scene_name)
{
	bool ret = false;
	JSON_Value* json_value = json_value_init_array();
	JSON_Array* json_array = json_value_get_array(json_value);

	ret = SaveGameObjects(json_array);
	if(ret == true)
	{
		LOG("Scene saved correctly!");
		
		std::string extension = ".json";
		std::string final_name = scene_name + extension;
		json_serialize_to_file_pretty(json_value, final_name.c_str());
		return ret;
	}
	else
	{
		LOG("Error saving scene")
		return ret;
	}
		
}


bool SerializationScene::SaveGameObjects(JSON_Array* json_array) {
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 1; iterator != App->scene_intro->GameObjects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator),json_array);

	}
	return true;
}

void SerializationScene::LoadScene(const char* name_scene)
{
	App->scene_intro->root->DeleteScene();

	JSON_Value* scene = json_parse_file(name_scene);
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

	}
	for (std::vector<GameObject*>::iterator iterator = App->scene_intro->GameObjects.begin()+1; iterator != App->scene_intro->GameObjects.end(); ++iterator) {

		GetHierarchy((*iterator));
	}
	for (std::vector<GameObject*>::iterator iterator = App->scene_intro->GameObjects.begin() + 1; iterator != App->scene_intro->GameObjects.end(); ++iterator) {

		if ((*iterator)->name.compare("Camera") == false) {
			App->scene_intro->camera_scene = (*iterator);
			//(*iterator) = nullptr;
		}

	}
	LOG("%s loaded correctly",name_scene);
}

void SerializationScene::GetHierarchy(GameObject* go)
{
	
		for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 1; iterator != App->scene_intro->GameObjects.end(); ++iterator)
		{
				if ((*iterator)->uuid_parent == go->uuid)
				{
					(*iterator)->parent = go;
					go->children.push_back((*iterator));
				}
		}
	
}