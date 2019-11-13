#include "Globals.h"
#include "Application.h"
#include "ModuleCamera3D.h"
#include "ModuleGameObject.h"
#include "Camera.h"

ModuleCamera3D::ModuleCamera3D(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	//CalculateViewMatrix();

	//X = vec3(1.0f, 0.0f, 0.0f);
	//Y = vec3(0.0f, 1.0f, 0.0f);
	//Z = vec3(0.0f, 0.0f, 1.0f);

	//Position = vec3(0.0f, 0.0f, 5.0f);
	//Reference = vec3(0.0f, 0.0f, 0.0f);

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

// -----------------------------------------------------------------
float* ModuleCamera3D::GetViewMatrix()
{
	return &ViewMatrix;
}