#include "SerializationScene.h"

SerializationScene::SerializationScene() 
{}

SerializationScene::~SerializationScene()
{

}

void SerializationScene::Update(float dt)
{

}

bool SerializationScene::SaveScene(const char* scene_name)
{
	bool ret = false;


	for (std::vector<GameObject*>::const_iterator iterator = App->scene_intro->GameObjects.begin() + 1; iterator != App->scene_intro->GameObjects.end(); iterator++)
	{

	}
	return ret;
}