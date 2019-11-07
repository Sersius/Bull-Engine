#include "Transform.h"
#include "ModuleLoadFBX.h"
#include "Application.h"
Transform::Transform(GameObject* parent) : Component(parent, COMPONENT_TYPE::TRANSFORM)
{}

Transform::~Transform()
{

}

void Transform::Update(float dt)
{

}

math::float4x4& Transform::GetLocalMatrix() const
{
	return float4x4::FromTRS(position, rotation, scale);
}

math::float4x4 Transform::GetGlobalMatrix() const
{
	float4x4 LocalMatrix = GetLocalMatrix();
	if (parent->parent != nullptr)
	{
		return parent->parent->transform->GetGlobalMatrix()* (LocalMatrix);
	}
	return LocalMatrix;
}
void Transform::SetPosition(float3 position)
{
	this->position = position;
}
void Transform::SetRotation(float3 rotation)
{
	this->rotation = Quat::FromEulerXYZ(rotation.x * DEGTORAD, rotation.y * DEGTORAD, rotation.z *DEGTORAD);
}