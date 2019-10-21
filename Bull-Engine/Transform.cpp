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

math::float4x4& Transform::GetMatrix() const
{
	return math::float4x4::FromTRS(position, rotation, scale);
}