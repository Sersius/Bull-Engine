#ifndef __MODULECOMPONENT_H__
#define __MODULECOMPONENT_H__

#include "ModuleGameObject.h"

class Component
{
public:
	Component(GameObject* parent, COMPONENT_TYPE type);
	~Component();

	void Update(float dt);

	void SetEnable(bool set);
	bool GetEnabled();

public:
	COMPONENT_TYPE type;
	bool active = true;
	GameObject* parent;
};

#endif