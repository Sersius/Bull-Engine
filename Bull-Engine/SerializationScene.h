#ifndef __SERIALIZATIONSCENE_H__
#define __SERIALIZATIONSCENE_H__


#include <vector>
#include "Globals.h"
#include "Application.h"
#include "ModuleGameObject.h"
#include "ModuleSceneIntro.h"
#include "Module.h"

#include "JSON/parson.h"

class SerializationScene
{
public:
	SerializationScene();
	~SerializationScene();

	void Update(float dt);

	bool SaveScene(const char* name_scene);
	bool SaveGameObjects(JSON_Array* json_array);
	void LoadScene(const char* name_scene);
	void GetHierarchy(GameObject* go);
public:
	std::string destination = ASSETS_SCENE_FOLDER;
	std::string final_path;

};

#endif