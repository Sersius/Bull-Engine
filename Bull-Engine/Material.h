#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "ModuleComponent.h"

class Material : public Component
{
public:
	Material(GameObject* parent);
	~Material();

	void Update(float dt);

private:

};

#endif