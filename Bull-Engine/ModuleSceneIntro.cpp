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
	root = new GameObject(nullptr);
	root->SetName("Root");
	game_objects.push_back(root);
	//App->loadFBX->LoadFbx("Models/BakerHouse.fbx");
	//App->loadFBX->LoadTexture("Textures/Baker_house.png");
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
	
	
	//App->loadFBX->LoadTexture(dropped_filedir);
	return UPDATE_CONTINUE;
}
GameObject* ModuleSceneIntro::CreateGameObject(GameObject* parent)
{
	GameObject* object = new GameObject(parent);
	object->SetName(App->loadFBX->name_mesh.c_str());
	game_objects.push_back(object);
	for (int i = 0; i < game_objects.capacity(); i++)
	{
		LOG("Name: %s",game_objects[i]->GetName());
	}
	LOG("GameObjects in scene: %d", game_objects.capacity());
	return object;
}



