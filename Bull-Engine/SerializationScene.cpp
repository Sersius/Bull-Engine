#include "Application.h"
#include "SerializationScene.h"



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

	SaveGameObjects(json_array);
	
	std::string extension = ".json";
	std::string final_name = scene_name + extension;
	
	json_serialize_to_file_pretty(json_value, final_name.c_str());
	return ret;
}


bool SerializationScene::SaveGameObjects(JSON_Array* json_array) {
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 2; iterator != App->scene_intro->GameObjects.end(); iterator++)
	{
		(*iterator)->SaveInfoGameObject((*iterator),json_array);

	}
	return true;
}