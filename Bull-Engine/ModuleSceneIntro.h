#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"
#include "Primitive.h"
#include "ModuleGameObject.h"

#include <vector>
//
//#include "MathGeoLib\include\Geometry\Sphere.h"
//#include "MathGeoLib\include\Math\float3.h"

class GameObject;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	
	GameObject* CreateGameObject(GameObject* parent);
	void CreateGameObjectMesh(char* path);
public:
	GameObject* root_object;
	GameObject* root;
	std::vector<GameObject*> game_objects;
	
};
