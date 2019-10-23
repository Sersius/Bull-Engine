#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleLoadFBX.h"
#include "Mesh.h"
#include "Material.h"


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
	root = CreateGameObject(nullptr);
	root->SetName("Root");
	//App->loadFBX->LoadFbx("Models/BakerHouse.fbx");
	/*gameobject_scene = CreateGameObject(root);
	gameobject_scene->SetName("BakerHouse");
	gameobject_scene->CreateComponent(COMPONENT_TYPE::MESH, "Models/BakerHouse.fbx");
	gameobject_scene->CreateComponent(COMPONENT_TYPE::MATERIAL, "Textures/Baker_house.png");
	gameobject_scene->material->GetTexture("Textures/Baker_house.png");
	root->CreateComponent(COMPONENT_TYPE::MATERIAL, "Assets/Meshes/BakerHouse.fbx");*/
	/*if (scene_gameobject->material)
		scene_gameobject->material->AssignTexture("Baker_house.png");
	for (int i = 0; i < scene_gameobject->GetNumChilds(); ++i)
		if (scene_gameobject->GetChild(i)->material)
			scene_gameobject->GetChild(i)->material->AssignTexture("Baker_house.png");*/
	
	////TEST-------------------------------------------------
	
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
	
	gameobject_scene;
	return UPDATE_CONTINUE;
}
GameObject* ModuleSceneIntro::CreateGameObject(GameObject* parent)
{
	GameObject* object = new GameObject(parent);
	//object->SetName(App->loadFBX->name_mesh.c_str());
	/*game_objects.push_back(object);*/
	/*for (int i = 0; i < game_objects.capacity(); i++)
	{
		LOG("Name: %s",game_objects[i]->GetName());
	}*/
	//LOG("GameObjects in scene: %d", game_objects.capacity());
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
}

GameObject * ModuleSceneIntro::GetSelectedGO() const
{
	return selected;
}


