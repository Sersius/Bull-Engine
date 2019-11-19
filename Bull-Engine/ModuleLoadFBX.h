#pragma once
#include "Module.h"
#include "Globals.h"
#include "Primitive.h"	
#include "ModuleGameObject.h"

#include "ParShapes/par_shapes.h"

class aiScene;
class aiNode;
class aiMesh;
class GameObject;

struct InfoFbx {
	uint id_index = 0; // index in VRAM
	uint num_index = 0;
	uint* index = nullptr;

	uint id_vertex = 0; // unique vertex in VRAM
	uint num_vertex = 0;
	float* vertex = nullptr;

	uint id_normals = 0;
	uint num_normals = 0;
	float* normals = 0;

	uint id_uvs = 0;
	uint num_uvs = 0;
	float* uvs = 0;

	vec3 position;
	vec3 rotation;
	vec3 scale;
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
	void LoadModelInfo(const aiScene* scene, aiNode* node, GameObject* game_object,const char* path);
	InfoFbx LoadParShapeMesh(par_shapes_mesh* mesh);
	void CreateBuffers();
	bool LoadTexture(char * path_texture, uint& texture_id);
	void FocusGameObject();
	bool ImportTexture(const char* file, const char* path, std::string& output_file);
	void ImporterMesh(std::string & output_file, Mesh* mesh, std::string name);
	bool LoadMesh(const void * buffer,GameObject* go);
	bool ImportMesh(const char* path,GameObject* go);
	uint texture_id;
public:
	GameObject* game_object = new GameObject(nullptr);
	std::string name_mesh;
	std::string texture_path;
	std::string path;
	InfoFbx mesh;
	GameObject* childGO;
	int texture_width = 0;
	int texture_height = 0;
	
};
