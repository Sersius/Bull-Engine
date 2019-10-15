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

	math::float4x4& GetMatrix() const;

public:
	math::float3 position = math::float3::zero;
	math::Quat rotation = math::Quat::identity;
	math::float3 scale = math::float3::one;
};

#endif