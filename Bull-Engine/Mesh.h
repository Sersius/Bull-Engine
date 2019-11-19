#ifndef __MESH_H__
#define __MESH_H__

#include "ModuleComponent.h"
#include "ModuleLoadFBX.h"

class Mesh : public Component
{
public:
	Mesh(GameObject* parent,char* path);
	Mesh();
	~Mesh();

	InfoFbx info_mesh;

	void Update(float dt);
	void GetMesh(char* path);
	void Draw();
	void DrawNormals();
	void SaveMesh(JSON_Array* componentsObj);
	void LoadMesh(JSON_Object* obj, GameObject* go);
public:
	bool active = true;
	std::string final_path;
	bool draw_normals = false;;
	const char* path = nullptr;
private:
	
};

#endif