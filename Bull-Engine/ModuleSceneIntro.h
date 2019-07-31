#pragma once
#include "Module.h"
#include "Globals.h"
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

public:
	uint my_id = 0;
	float vertexs[200];
	float v0[3] = { 1.0f, 1.0f, 0.0f };
	float v1[3] = { 0.0f, 1.0f, 0.0f };
	float v2[3] = { 0.0f, 0.0f, 0.0f };
	float v3[3] = { 1.0f, 0.0f, 0.0f };
	float vertex[4] = { *v0,*v1,*v2,*v3 };
};
