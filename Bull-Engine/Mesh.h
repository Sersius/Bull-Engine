#ifndef __MESH_H__
#define __MESH_H__

#include "ModuleComponent.h"

class Mesh : public Component
{
public:
	Mesh(GameObject* parent);
	~Mesh();

	void Update(float dt);

private:

};

#endif