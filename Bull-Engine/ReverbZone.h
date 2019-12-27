#ifndef REVERBZONE_H
#define REVERBZONE_H

#include "ModuleComponent.h"
#include "Globals.h"
#include "MathGeoLib\include\MathGeoLib.h"

class GameObject;

class ReverbZone : public Component
{
public:
	ReverbZone(GameObject* parent);
	~ReverbZone();

	void Update(float dt);
	void SetRadius(float rad);
	void DebugDrawSphere();

	void SaveReverbZone(JSON_Array* componentsObj) const;
	void LoadReverbZone(JSON_Object* obj, GameObject* go);

public:
	float radius = 10.0f;

private:
	math::Sphere sphere;

};

#endif