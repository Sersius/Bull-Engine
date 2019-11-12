#include "SerializationScene.h"
#include "JSON/parson.h"
#include "Config.h"

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

	

	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 2; iterator != App->scene_intro->GameObjects.end(); iterator++)
	{
		(*iterator)->SaveInfo();
	}

	Save(scene_name);
	return ret;
}

void SerializationScene::Save(const char* scene_name)
{
	bool returned = false;
	std::string extension = ".json";
	std::string final_name = scene_name + extension;
	JSON_Value*	json_root = json_value_init_array();
	json_serialize_to_file_pretty(json_root, final_name.c_str());
	

}

