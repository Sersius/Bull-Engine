#ifndef __MODULEGAMEOBJECT_H__
#define __MODULEGAMEOBJECT_H__

#include "Globals.h"

#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>
#include <string>


enum COMPONENT_TYPE
{
	NONE = 0,
	TRANSFORM,
	MESH,
	MATERIAL
};

class Component;
class Material;
class Mesh;
class Transform;

class GameObject
{
public:

	GameObject(GameObject* parent = nullptr);
	~GameObject();

	void Update(float dt);

	Component* CreateComponent(COMPONENT_TYPE type, char* name="");
	Material* GetComponentMaterial() const;
	Mesh* GetComponentMesh() const;
	Transform* GetComponentTransform() const;
	Component* GetComponent(COMPONENT_TYPE type) const;
	void SetName(const char* new_name);
	const char* GetName()const;
	void BlitHierarchy(GameObject* root);
	void BoundingBox();
	
public:
	AABB bounding_box;
	std::vector<GameObject*> children;
	Material* material = nullptr;
	Mesh* mesh = nullptr;
	Transform* transform = nullptr;
	bool render_model = true;
	bool is_primitive = false;
private:
	std::string name;
	GameObject* parent = nullptr;
	std::vector<Component*> components;
};

#endif