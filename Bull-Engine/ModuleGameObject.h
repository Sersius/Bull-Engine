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

	GameObject(GameObject* parent = nullptr);
	~GameObject();

	void Update(float dt);

	Component* CreateComponent(COMPONENT_TYPE type, std::string name);
	Component* GetComponent(COMPONENT_TYPE type, std::string name);
	void SetName(const char* new_name);
	const char* GetName()const;
	std::vector<GameObject*> children;

private:

	std::string name;
	
	GameObject* parent = nullptr;
	
	std::vector<Component*> components;
};

#endif