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
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);

	//json_object_set_value(componentObj, "Position", component);
	json_object_set_number(componentObj, "PositionX", position.x);
	json_object_set_number(componentObj, "PositionY", position.y);
	json_object_set_number(componentObj, "PositionZ", position.z);
	json_object_set_number(componentObj, "RotationX", rotation.x);
	json_object_set_number(componentObj, "RotationY", rotation.y);
	json_object_set_number(componentObj, "RotationZ", rotation.z);
	json_object_set_number(componentObj, "ScaleX", scale.x);
	json_object_set_number(componentObj, "ScaleY", scale.x);
	json_object_set_number(componentObj, "ScaleZ", scale.x);

	json_array_append_value(componentsObj, component);
}