#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "ModuleComponent.h"


class Camera : public Component
{
public:
	Camera(GameObject* parent);
	~Camera();

	void Update(float dt);

	void LookAt(const float3 &Spot);

	void SetFOV(float fov);
	void SetAspectRatio(float aspect_ratio);

private:
	Frustum frustrum;
	bool frustrum_culling;

};

#endif;