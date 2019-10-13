#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"	

class aiScene;
class aiNode;
struct InfoFbx {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	uint* vertex = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = 0;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = 0;
};
class ModuleLoadFBX : public Module
{
public:
	ModuleLoadFBX(Application* app, bool start_enabled = true);
	~ModuleLoadFBX();

	bool Start();
	update_status Update(float dt);
	update_status PreUpdate(float dt);
	bool CleanUp();
	bool LoadFbx(const char* path);
	void LoadModelInfo(const aiScene* scene, aiNode* node,const char* path);
	void LoadTexture(char * path_texture);
	uint texture_id;
public:

	InfoFbx mesh;
	
};
