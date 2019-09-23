#pragma once
#include "Module.h"
#include "Globals.h"
#include "ImGui/imgui.h"
#include "Primitive.h"
//
//#include "MathGeoLib\include\Geometry\Sphere.h"
//#include "MathGeoLib\include\Math\float3.h"



class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	//Sphere s1, s2;
	

public:
	
	
};
