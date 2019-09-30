#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleLoadFBX.h"


ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	glewInit();

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));
	/*s1.pos = { 0,0,0 };
	s1.r = 10;

	s2.pos = { 0,0,0 };
	s2.r = 5;*/

	App->loadFBX->LoadFbx("");
	return ret;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	
	return(UPDATE_CONTINUE);
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	//if (s1.Intersects(s2))
	//{
	//	LOG("They intersect");
	//	
	//}
	App->renderer3D->DrawModel(App->loadFBX->mesh);

	return UPDATE_CONTINUE;
}



