#ifndef __MESH_H__
#define __MESH_H__

#include "ModuleComponent.h"
#include "ModuleLoadFBX.h"

class Mesh : public Component
{
public:
	Mesh(GameObject* parent,char* path);
	~Mesh();

	void Update(float dt);
	void GetMesh(char* path);
	InfoFbx info_mesh;
private:
	char* path = nullptr;
};

#endif