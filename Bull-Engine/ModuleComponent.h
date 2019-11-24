#ifndef __MODULECOMPONENT_H__
#define __MODULECOMPONENT_H__

#include "ModuleGameObject.h"

class GameObject;
enum COMPONENT_TYPE;
class Component
{
public:
	Component(GameObject* parent, COMPONENT_TYPE type);
	~Component();

	void Update(float dt);

public:
	COMPONENT_TYPE type;
	
	GameObject* parent;
};

#endif