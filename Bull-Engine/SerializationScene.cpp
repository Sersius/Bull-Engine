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

	SceneConfig* scene_config = new SceneConfig();
	scene_config->SetArray();
	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 2; iterator != App->scene_intro->GameObjects.end(); iterator++)
	{
		(*iterator)->SaveInfo(scene_config);
	}

	scene_config->Save(scene_name);
	return ret;
}



