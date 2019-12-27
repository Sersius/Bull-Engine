#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "TimerInGame.h"
#include "ModuleGameObject.h"

#include <vector>

#include "ImGui/imgui.h"


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
	void CreateGameObjectMaterial(char* path,GameObject* gameobject);
	void SetSelectedGameObject(const GameObject* target);
	void UnselectGameObject();
	GameObject* GetSelectedGO() const;
	bool want_to_load = false;
	bool want_to_save = false;
	
public:
	std::vector<GameObject*> GameObjects;
	GameObject* root = nullptr;
	GameObject* gameobject_scene = nullptr;
	GameObject* GOPath = nullptr;
	GameObject* reverb_zone = nullptr;
	GameObject* camera_scene = nullptr;
	GameObject* selected = nullptr;
	TimerInGame timer_in_game;

	bool game_running = false;
	
	
};
