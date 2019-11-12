#ifndef __SERIALIZATIONSCENE_H__
#define __SERIALIZATIONSCENE_H__


#include <vector>
#include "Application.h"
#include "ModuleGameObject.h"
#include "ModuleSceneIntro.h"
#include "Module.h"

class SerializationScene
{
public:
	SerializationScene();
	~SerializationScene();

	void Update(float dt);

	
	bool SaveScene(const char* name_scene);
	
public:
	

};

#endif