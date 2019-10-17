#include "Mesh.h"
#include "Application.h"
#include "ModuleLoadFBX.h"

Mesh::Mesh(GameObject* parent,char* path) : Component(parent, COMPONENT_TYPE::MESH), path(path)
{
	GetMesh(path);
}

Mesh::~Mesh()
{

}

void Mesh::Update(float dt)
{

}

void Mesh::GetMesh(char* path)
{
	App->loadFBX->LoadFbx(path);
	this->path = path;
}