#include "Transform.h"
#include "ModuleLoadFBX.h"
#include "Application.h"
#include "Camera.h"
#include "InspectorWindow.h"
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
	if (parent->GetComponentCamera() != nullptr) {
		parent->GetComponentCamera()->frustum.pos = position;
	}
}
void Transform::SetRotation(float3 rotation)
{
	this->rotation = Quat::FromEulerXYZ(rotation.x * DEGTORAD, rotation.y * DEGTORAD, rotation.z *DEGTORAD);
	
}

void Transform::SaveTransform(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentGO = json_value_get_object(component);

	json_object_set_number(componentGO, "Type:", this->type);
	json_object_set_number(componentGO, "PositionX", position.x);
	json_object_set_number(componentGO, "PositionY", position.y);
	json_object_set_number(componentGO, "PositionZ", position.z);
	json_object_set_number(componentGO, "RotationX", rotation.x);
	json_object_set_number(componentGO, "RotationY", rotation.y);
	json_object_set_number(componentGO, "RotationZ", rotation.z);
	json_object_set_number(componentGO, "ScaleX", scale.x);
	json_object_set_number(componentGO, "ScaleY", scale.y);
	json_object_set_number(componentGO, "ScaleZ", scale.z);

	json_array_append_value(componentsObj, component);
}

void Transform::LoadTransform(JSON_Object* obj)
{
	position.x = json_object_get_number(obj, "PositionX");
	position.y = json_object_get_number(obj, "PositionY");
	position.z = json_object_get_number(obj, "PositionZ");
	rotation.x = json_object_get_number(obj, "RotationX");
	rotation.y = json_object_get_number(obj, "RotationY");
	rotation.z = json_object_get_number(obj, "RotationZ");
	scale.x = json_object_get_number(obj, "ScaleX");
	scale.y = json_object_get_number(obj, "ScaleY");
	scale.z = json_object_get_number(obj, "ScaleZ");	
}