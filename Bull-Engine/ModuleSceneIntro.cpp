#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleLoadFBX.h"

#include "Material.h"
#include "Mesh.h"

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

	App->camera->Move(float3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(float3(0, 0, 0));
	root = CreateGameObject(nullptr);
	root->SetName("Root");
	
	gameobject_scene = CreateGameObject(root);
	gameobject_scene->SetName("BakerHouse");
	gameobject_scene->CreateComponent(COMPONENT_TYPE::MESH, "Library/Models/BakerHouse.fbx");
	gameobject_scene->children.at(0)->material->GetTexture("Library/Textures/Baker_house.png");
	gameobject_scene->children.at(1)->material->GetTexture("Library/Textures/Baker_house.png");

	camera_scene = CreateGameObject(root);
	camera_scene->CreateComponent(COMPONENT_TYPE::CAMERA);
	camera_scene->SetName("Camera");
	
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
	PlaneG p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	
	root->Update(dt);
	return UPDATE_CONTINUE;
}

GameObject* ModuleSceneIntro::CreateGameObject(GameObject* parent)
{
	GameObject* object = new GameObject(parent);
	return object;
}

void ModuleSceneIntro::CreateGameObjectMesh(char* path)
{
	gameobject_scene = CreateGameObject(root);
	std::string name_model =path;
	std::string base_filename = name_model.substr(name_model.find_last_of("/\\") + 1);
	std::string::size_type const p(base_filename.find_last_of('.'));
	std::string file_without_extension = base_filename.substr(0, p);
	gameobject_scene->SetName(file_without_extension.c_str());
	gameobject_scene->CreateComponent(COMPONENT_TYPE::MESH,path);
}

void ModuleSceneIntro::CreateGameObjectMaterial(char* path, GameObject* gameobject)
{
	gameobject->material->GetTexture(path);

	for (int i = 0; i < gameobject->children.size(); i++)
	{
		
		CreateGameObjectMaterial(path, gameobject->children[i]);
	}

}

void ModuleSceneIntro::SetSelectedGameObject(const GameObject * target)
{
	selected = (GameObject*)target;
	selected->is_selected = true;
}

void ModuleSceneIntro::UnselectGameObject()
{
	if (selected)
		selected->is_selected = false;
	selected = nullptr;

}

GameObject * ModuleSceneIntro::GetSelectedGO() const
{
	return selected;
}



