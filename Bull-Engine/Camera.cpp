#include "Camera.h"

Camera::Camera(GameObject * parent) : Component(parent, COMPONENT_TYPE::MATERIAL)
{
}

Camera::~Camera()
{
}

void Camera::Update(float dt)
{
}

void Camera::LookAt(const float3 & Spot)
{
}

void Camera::SetFOV(float fov)
{
}

void Camera::SetAspectRatio(float aspect_ratio)
{
}
