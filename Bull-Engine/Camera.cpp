#include "Camera.h"

#include "Glew\include\glew.h"

#define ASPECT_RATIO 1.78f

Camera::Camera(GameObject * parent) : Component(parent, COMPONENT_TYPE::CAMERA)
{
	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = -float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::DegToRad(60.0f);

	SetAspectRatio(ASPECT_RATIO);
}

Camera::~Camera()
{
}

void Camera::Update(float dt)
{
}

float Camera::GetNear() const
{
	return frustum.nearPlaneDistance;
}

float Camera::GetFar() const
{
	return frustum.farPlaneDistance;
}

float Camera::GetFOV() const
{
	return math::RadToDeg(frustum.verticalFov);
}

float Camera::GetApectRatio() const
{
	return frustum.AspectRatio();
}

float4x4 Camera::GetViewMatrix() const
{
	math::float4x4 matrix = frustum.ViewMatrix();

	return 	matrix.Transposed();
}

float4x4 Camera::GetProjectionMatrix() const
{
	math::float4x4 matrix = frustum.ProjectionMatrix();

	return 	matrix.Transposed();
}

void Camera::SetNear(float distance)
{
	frustum.nearPlaneDistance = distance;
}

void Camera::SetFar(float distance)
{
	frustum.farPlaneDistance = distance;
}

void Camera::SetFOV(float fov)
{
	frustum.verticalFov = fov * DEGTORAD;
	frustum.horizontalFov = 2.0f * atanf(ASPECT_RATIO * tanf(frustum.verticalFov / 2.0f));
}

void Camera::SetAspectRatio(float aspect_ratio)
{
	frustum.horizontalFov = 2.0f * atanf(tanf(frustum.verticalFov / 2.0f) * aspect_ratio);
}

void Camera::LookAt(const float3 &Spot)
{
	float3 direcction = Spot - frustum.pos;

	float3x3 look_mat = float3x3::LookAt(frustum.front, direcction.Normalized(), frustum.up, float3::unitY);

	frustum.front = look_mat.MulDir(frustum.front).Normalized();
	frustum.up = look_mat.MulDir(frustum.up).Normalized();
}

void Camera::DebugDraw()
{
	glBegin(GL_LINES);
	glLineWidth(2.0f);
	glColor4f(0.0f, 1.0f, 0.0f, 1.0f);

	for (uint i = 0; i < frustum.NumEdges(); i++) {

		glVertex3f(frustum.Edge(i).a.x, frustum.Edge(i).a.y, frustum.Edge(i).a.z);
		glVertex3f(frustum.Edge(i).b.x, frustum.Edge(i).b.y, frustum.Edge(i).b.z);
	}

	glEnd();
	glColor4f(1.0f, 1.0f, 1.0f, 1.0f);
}