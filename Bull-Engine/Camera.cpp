#include "Camera.h"
#include "Mesh.h"
#include "Application.h"

#include "Glew\include\glew.h"

#define ASPECT_RATIO 1.78f

Camera::Camera(GameObject * parent) : Component(parent, COMPONENT_TYPE::CAMERA)
{
	frustum.type = FrustumType::PerspectiveFrustum;

	frustum.pos = float3::zero;
	frustum.front = float3::unitZ;
	frustum.up = float3::unitY;

	frustum.nearPlaneDistance = 1.0f;
	frustum.farPlaneDistance = 100.0f;
	frustum.verticalFov = math::DegToRad(60.0f);
	
	SetAspectRatio(ASPECT_RATIO);
}

Camera::~Camera()
{
	if (parent)
		parent->camera = nullptr;
}


void Camera::Update(float dt)
{
	if (App->scene_intro->game_running == true) {
		if (App->scene_intro->root)
		{
			FrustumCulling(App->scene_intro->root);		
		}
	}
	DebugDraw();
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

	return matrix.Transposed();
}

float4x4 Camera::GetProjectionMatrix() const
{
	math::float4x4 matrix = frustum.ProjectionMatrix();

	return matrix.Transposed();
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

void Camera::FrustumCulling(GameObject * gameobject)
{
	if (gameobject) {
		if (!gameobject->camera)
		{
			for (std::vector<GameObject*>::const_iterator it = gameobject->children.begin(); it < gameobject->children.end(); it++)
			{
				AABB refBox = (*it)->bounding_box;

				if (refBox.IsFinite() && (*it)->mesh && (*it)->mesh->info_mesh.num_vertex > 0)
				{

					if (ContainsAaBox(refBox) == OUTSIDE)
					{
						(*it)->mesh->active = false;
					}
					else
						(*it)->mesh->active = true;
				}

				FrustumCulling(*it);

			}
		}
	}
}

int Camera::ContainsAaBox(const AABB & refbox)
{
	math::float3 vCorner[8];
	int iTotalIn = 0;
	refbox.GetCornerPoints(vCorner); // get the corners of the box into the vCorner array
									 // test all 8 corners against the 6 sides
									 // if all points are behind 1 specific plane, we are out
									 // if we are in with all points, then we are fully in
	math::Plane m_plane[6];
	frustum.GetPlanes(m_plane); //{ near, far, left, right, top, bottom }.

	for (int p = 0; p < 6; ++p)
	{
		int iInCount = 8;
		int iPtIn = 1;
		for (int i = 0; i < 8; ++i) 
		{
			// test this point against the planes

			if (m_plane[p].IsOnPositiveSide(vCorner[i])) 
			{
				iPtIn = 0;
				--iInCount;
			}
		}
		// were all the points outside of plane p?
		if (iInCount == 0)
			return(OUTSIDE);
		// check if they were all on the right side of the plane
		iTotalIn += iPtIn;
	}
	// so if iTotalIn is 6, then all are inside the view
	if (iTotalIn == 6)
		return(INSIDE);
	// we must be partly in then otherwise
	return(INTERSECT);
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

void Camera::SaveCamera(JSON_Array* componentsObj)
{
	JSON_Value* component = json_value_init_object();
	JSON_Object* componentObj = json_value_get_object(component);

	json_object_set_number(componentObj, "Type:", this->type);
		
	json_object_set_number(componentObj, "Near Distance:", frustum.nearPlaneDistance);
	json_object_set_number(componentObj, "Far Distance:", frustum.farPlaneDistance);
	json_object_set_number(componentObj, "Frustum Vertical FOV:", frustum.verticalFov);
	json_object_set_number(componentObj, "Frustum Horizontal FOV:", frustum.horizontalFov);
	


	json_array_append_value(componentsObj, component);

}

void Camera::LoadCamera(JSON_Object* obj, GameObject* go)
{
	go->camera->frustum.nearPlaneDistance = json_object_get_number(obj, "Near Distance:");
	go->camera->frustum.farPlaneDistance = json_object_get_number(obj, "Far Distance:");
	go->camera->frustum.verticalFov = json_object_get_number(obj, "Frustum Vertical FOV:");
	go->camera->frustum.horizontalFov = json_object_get_number(obj, "Frustum Horizontal FOV:");

}