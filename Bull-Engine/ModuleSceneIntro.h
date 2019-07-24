#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"
#include "ImGui/imgui.h"


#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	//HARDWARE
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	SDL_version version;
	int CPU_Cache = 0;
	int CPU_Count = 0;
	int ram = 0;
public:

};
