#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"
#include "Mesh.h"
#include "Transform.h"
#include "Camera.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//Dummy camera
	dummy = new Camera(nullptr);
	dummy->SetNear(0.1f);
	dummy->SetFar(1000.0f);
	Move({ 5.0f, 5.0f, 5.0f });
	LookAt({ 0.0f, 0.0f, 0.0f });
}

ModuleCamera3D::~ModuleCamera3D()
{}

// -----------------------------------------------------------------
bool ModuleCamera3D::Start()
{
	LOG("Setting up the camera");
	bool ret = true;

	return ret;
}

// -----------------------------------------------------------------
bool ModuleCamera3D::CleanUp()
{
	LOG("Cleaning camera");

	return true;
}

// -----------------------------------------------------------------
update_status ModuleCamera3D::Update(float dt)
{
	// Implement a debug camera with keys and mouse
	// Now we can make this movememnt frame rate independant!

	float3 newPos(0,0,0);
	float speed = 2.5f * dt;
	float wheel_speed = 3.0f;
	float sensibility = 0.25f * dt;

	if(App->input->GetKey(SDL_SCANCODE_LSHIFT) == KEY_REPEAT)
		speed = 6.0f * dt;

	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		if (dx != 0)
		{
			Quat quat = Quat::RotateY(dx * sensibility);
			
			dummy->frustum.up = quat.Mul(dummy->frustum.up).Normalized();
			dummy->frustum.front = quat.Mul(dummy->frustum.front).Normalized();
		}

		if (dy != 0)
		{
			Quat quat = Quat::RotateAxisAngle(dummy->frustum.WorldRight(), dy * sensibility);
			float3 up = quat.Mul(dummy->frustum.up).Normalized();

			if (up.y > 0.0f) {
				dummy->frustum.up = up;
				dummy->frustum.front = quat.Mul(dummy->frustum.front).Normalized();
			}
		}

	}
	//FREE LOOK
	if (App->input->GetMouseButton(SDL_BUTTON_RIGHT) == KEY_REPEAT) {
		if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_REPEAT) newPos.y += speed;
		if (App->input->GetKey(SDL_SCANCODE_E) == KEY_REPEAT) newPos.y -= speed;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT) newPos += dummy->frustum.front * speed;
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) newPos -= dummy->frustum.front * speed;

		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) newPos -= dummy->frustum.WorldRight() * speed;
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) newPos += dummy->frustum.WorldRight() * speed;

		Move(newPos);
	}

	//FOCUS ON SELECTED
	if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
	{
		App->loadFBX->FocusGameObject();
	}

	//MOUSE WHEEL
	if (App->input->GetMouseZ())
	{
		newPos += dummy->frustum.front * wheel_speed * App->input->GetMouseZ();
		Move(newPos);
	}

	if (App->input->GetMouseButton(SDL_BUTTON_MIDDLE) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = App->input->GetMouseYMotion();

		newPos += dummy->frustum.WorldRight() * dx * sensibility;
		newPos += dummy->frustum.up * dy *  sensibility;

		dummy->frustum.Translate(newPos);
	}
	// ROTATE 
	if(App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_REPEAT)
	{
		int dx = -App->input->GetMouseXMotion();
		int dy = -App->input->GetMouseYMotion();

		if (dx != 0)
		{
			Quat quat = Quat::RotateY(dx * sensibility);

			dummy->frustum.up = quat.Mul(dummy->frustum.up).Normalized();
			dummy->frustum.front = quat.Mul(dummy->frustum.front).Normalized();
		}

		if (dy != 0)
		{
			Quat quat = Quat::RotateAxisAngle(dummy->frustum.WorldRight(), dy * sensibility);
			float3 up = quat.Mul(dummy->frustum.up).Normalized();

			if (up.y > 0.0f) {
				dummy->frustum.up = up;
				dummy->frustum.front = quat.Mul(dummy->frustum.front).Normalized();
			}
		}
	}

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_REPEAT)
	{
		App->serialization->SaveScene("SceneSaved");
	}
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		App->serialization->LoadScene("Scene_1.json");
	}
	
	if (!ImGui::GetIO().WantCaptureMouse) {
		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN && App->input->GetKey(SDL_SCANCODE_LALT) == KEY_IDLE)
		{
			float width = (float)App->width;
			float height = (float)App->height;

			int mouse_x = App->input->GetMouseX();
			int mouse_y = App->input->GetMouseY();

			float mouse_x_norm = -(1.0f - ((float)mouse_x * 2.0f) / width);
			float mouse_y_norm = 1.0f - ((float)mouse_y * 2.0f) / height;

			//mouse_x_norm = (mouse_x_norm - 0.5) / 0.5;
			//mouse_y_norm = -(mouse_y_norm - 0.5) / 0.5;

			picking = dummy->frustum.UnProjectLineSegment(mouse_x_norm, mouse_y_norm);

			GameObject* near_go = nullptr;
			GameObject* root_go = App->scene_intro->root;
			float min_dist = inf;
			std::vector<GameObject*> all_go_touched;

			for (int i = 0; i < root_go->children.size(); ++i) {
				TestRayWithAABB(picking, near_go, root_go->children[i], min_dist, all_go_touched);
			}

			if (near_go) {
				if (TestRayWithTriangles(all_go_touched, picking, near_go))
					App->scene_intro->SetSelectedGameObject(near_go);
				else
					App->scene_intro->UnselectGameObject();
			}
			else
				App->scene_intro->UnselectGameObject();
		}
	}

	DrawDebugRay();

	return UPDATE_CONTINUE;
}

// -----------------------------------------------------------------
void ModuleCamera3D::Look(const float3 &Position, const float3 &Reference, bool RotateAroundReference)
{
	dummy->frustum.pos = Position;
	LookAt(Reference);
}

// -----------------------------------------------------------------
void ModuleCamera3D::LookAt(const float3 &Spot)
{
	math::float3 Z = -(dummy->frustum.pos - Spot).Normalized();
	math::float3 X = math::Cross(math::float3(0.0f, 1.0f, 0.0f), Z).Normalized();
	math::float3 Y = math::Cross(Z, X);

	dummy->frustum.front = Z;
	dummy->frustum.up = Y;
}


// -----------------------------------------------------------------
void ModuleCamera3D::Move(const float3 &Movement)
{
	dummy->frustum.Translate(Movement);
}

void ModuleCamera3D::TestRayWithAABB(LineSegment ray, GameObject* &posible_go, GameObject* all_posible_go, float &distance, std::vector<GameObject*> &all_go_touched)
{
	if (all_posible_go->bounding_box.IsFinite())
	{
		float dist_hit = 0.0f, far_dist_hit = 0.0f;

		if (ray.Intersects(all_posible_go->bounding_box, dist_hit, far_dist_hit))
		{
			all_go_touched.push_back(all_posible_go);

			if (dist_hit < distance)
			{
				posible_go = all_posible_go;
				distance = dist_hit;
			}
		}
	}

	for (int i = 0; i < all_posible_go->children.size(); ++i) {
		TestRayWithAABB(ray, posible_go, all_posible_go->children[i], distance, all_go_touched);
	}

}

bool ModuleCamera3D::TestRayWithTriangles(std::vector<GameObject*>& all_go_touched, LineSegment ray, GameObject *& posible_go)
{
	bool ret = false;

	InfoFbx go_info = InfoFbx();
	Mesh* go_mesh = nullptr;
	Transform* go_trans = nullptr;

	float min_dist = inf;

	for (int i = 0; i < all_go_touched.size(); ++i) {
		Triangle near_tri;

		go_trans = all_go_touched[i]->GetComponentTransform();

		if (go_trans != nullptr)
		{
			LineSegment local_ray(ray);
			local_ray.Transform(go_trans->GetGlobalMatrix().Inverted());

			go_mesh = all_go_touched[i]->GetComponentMesh();

			if (go_mesh != nullptr)
			{
				go_info = go_mesh->info_mesh;

				for (int j = 0; j < go_info.num_index; ++j) {
					near_tri.a = { go_info.vertex[go_info.index[j] * 3], go_info.vertex[go_info.index[j] * 3 + 1], go_info.vertex[go_info.index[j] * 3 + 2] };
					near_tri.b = { go_info.vertex[go_info.index[j] * 3 + 2], go_info.vertex[go_info.index[j] * 3 + 3], go_info.vertex[go_info.index[j] * 3 + 4] };
					near_tri.c = { go_info.vertex[go_info.index[j] * 3 + 3], go_info.vertex[go_info.index[j] * 3 + 4], go_info.vertex[go_info.index[j] * 3 + 5] };

					float dist_hit = 0.0f;
					float3	far_dist_hit = float3::zero;

					if (local_ray.Intersects(near_tri, &dist_hit, &far_dist_hit))
					{
						ret = true;

						if (dist_hit < min_dist)
						{
							min_dist = dist_hit;
							posible_go = all_go_touched[i];
						}
					}
				}
			}
		}
	}

	return ret;
}

void ModuleCamera3D::DrawDebugRay()
{
	glColor4f(1, 0, 0, 1);

	//Between-planes right
	GLfloat pointA[3] = { picking.a.x, picking.a.y, picking.a.z };
	GLfloat pointB[3] = { picking.b.x, picking.b.y, picking.b.z };

	glBegin(GL_LINES);
	glVertex3fv(pointA);
	glVertex3fv(pointB);
	glEnd();

	glColor4f(1, 1, 1, 1);
}
