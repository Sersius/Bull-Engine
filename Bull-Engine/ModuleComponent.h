#ifndef __MODULECOMPONENT_H__
#define __MODULECOMPONENT_H__

#include "ModuleGameObject.h"

class ModuleComponent
{
public:
	ModuleComponent();
	~ModuleComponent();

	void Update(float dt);

	void SetEnable(bool set);
	bool GetEnabled();

public:
	COMPONENT_TYPE type;
	bool active = true;
	ModuleGameObject* parent;
};

#endif