#pragma once
#include "Module.h"
#include "Globals.h"
#include "glmath.h"
#include "Light.h"
#include "ModuleLoadFBX.h"

#include "Glew/include/glew.h"

#include <vector>

#define MAX_LIGHTS 8
#define CHECKERS_HEIGHT 64
#define CHECKERS_WIDTH 64

class ModuleRenderer3D : public Module
{
public:
	ModuleRenderer3D(Application* app, bool start_enabled = true);
	~ModuleRenderer3D();

	bool Init();
	update_status PreUpdate(float dt);
	update_status PostUpdate(float dt);
	bool CleanUp();

	void Checkers();
	void OnResize(int width, int height);
	void RendererSettings(int enum_, bool type_render);
public:
	std::vector<Mesh*> meshes;
	Light lights[MAX_LIGHTS];
	SDL_GLContext context;
	mat3x3 NormalMatrix;
	mat4x4 ModelMatrix, ViewMatrix, ProjectionMatrix;
	bool wireframe = false;
	uint ImageName=0;
};