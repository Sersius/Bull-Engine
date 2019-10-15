#ifndef __MODULEGAMEOBJECT_H__
#define __MODULEGAMEOBJECT_H__

#include <vector>
#include <string>
#include "Globals.h"

enum COMPONENT_TYPE
{
	NONE = 0,
	TRANSFORM,
	MESH,
	MATERIAL
};

class Component;

class GameObject
{
public:

	GameObject(std::string name, GameObject* parent = nullptr);
	~GameObject();

	void Update(float dt);

	Component* CreateComponent(COMPONENT_TYPE type, std::string name);
	Component* GetComponent(COMPONENT_TYPE type, std::string name);

private:

	std::string name;
	GameObject* parent = nullptr;
	std::vector<GameObject*> children;
	std::vector<Component*> components;
};

#endif