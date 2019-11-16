#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"

class ModuleCamera3D : public Module
{
public:
	ModuleCamera3D(Application* app, bool start_enabled = true);
	~ModuleCamera3D();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference = false);
	void LookAt(const float3 &Spot);
	void Move(const float3 &Movement);
	float* GetViewMatrix();

	void TestRayWithAABB(LineSegment ray, GameObject* &posible_go, GameObject* all_posible_go, float &distance, std::vector<GameObject*> &all_go_touched);

public:
	Camera* dummy = nullptr;

private:
	mat4x4 ViewMatrix, ViewMatrixInverse;
	LineSegment picking;

};