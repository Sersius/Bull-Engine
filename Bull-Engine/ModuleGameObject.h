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

class ModuleComponent;

class ModuleGameObject
{
public:

	ModuleGameObject(std::string name, ModuleGameObject* parent = nullptr);
	~ModuleGameObject();

	void Update(float dt);

	ModuleComponent* CreateComponent(COMPONENT_TYPE type, std::string name);
	ModuleComponent* GetComponent(COMPONENT_TYPE type, std::string name);

private:

	std::string name;
	ModuleGameObject* parent = nullptr;
	std::vector<ModuleGameObject*> children;
	std::vector<ModuleComponent*> components;
};

#endif