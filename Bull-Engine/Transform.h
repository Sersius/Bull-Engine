#ifndef __TRANSFORM_H__
#define __TRANSFORM_H__

#include "ModuleComponent.h"

#include "MathGeoLib/include/Math/float3.h"
#include "MathGeoLib/include/Math/Quat.h"
#include "MathGeoLib/include/Math/float4x4.h"

class Transform : Component
{
public:
	Transform(GameObject* parent);
	~Transform();

	void Update(float dt);

	math::float4x4& GetLocalMatrix() const;
	math::float4x4 GetGlobalMatrix() const;

	void SetPosition(float3 position);
	void SetRotation(float3 rotation);

	void SetMatrixFromGlobal(float4x4 &global_matrix);

	void SaveTransform(JSON_Array* componentsObj) const;
	void LoadTransform(JSON_Object* obj);
public:
	math::float3 position = math::float3::zero;
	math::Quat rotation = math::Quat::identity;
	math::float3 scale = math::float3::one;
	
	math::float4x4 transform_matrix = math::float4x4::identity;
	
};

#endif