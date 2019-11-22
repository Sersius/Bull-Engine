#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ModuleComponent.h"
#include "Globals.h"

class GameObject;

enum Intersection {
	OUTSIDE = 0,
	INSIDE,
	INTERSECT
};

class Camera : public Component
{
public:
	Camera(GameObject* parent);
	~Camera();

	void Update(float dt);

	float GetNear() const;
	float GetFar() const;
	float GetFOV() const;
	float GetApectRatio() const;

	float4x4 GetViewMatrix() const;
	float4x4 GetProjectionMatrix() const;

	void SetNear(float distance);
	void SetFar(float distance);
	void SetFOV(float fov);
	void SetAspectRatio(float aspect_ratio);

	void LookAt(const float3 &Spot);

	void FrustumCulling(GameObject* gameobject);
	int ContainsAaBox(const AABB &refbox);

	void DebugDraw();
	void SaveCamera(JSON_Array* componentsObj);
	void LoadCamera(JSON_Object* obj, GameObject* go);
public:

	Frustum frustum;

private:

	bool frustum_culling;

};

#endif;