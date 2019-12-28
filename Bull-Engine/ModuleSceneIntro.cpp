#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "ModuleLoadFBX.h"

#include "Material.h"
#include "Mesh.h"
#include "Transform.h"
#include "AudioEmitter.h"
#include "ReverbZone.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	WwiseT::CloseSoundEngine();
}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	glewInit();

	App->camera->Move(float3(0.0f, 10.0f, 30.0f));
	App->camera->LookAt(float3(0, 0, 0));
	root = CreateGameObject(nullptr);
	root->SetName("Root");
	
	gameobject_scene = CreateGameObject(root);
	gameobject_scene->SetName("Source/Listener");
	gameobject_scene->CreateComponent(COMPONENT_TYPE::AUDIO_EMITTER);
	gameobject_scene->CreateComponent(COMPONENT_TYPE::AUDIO_LISTENER);
	gameobject_scene->CreateComponent(COMPONENT_TYPE::MESH,"Assets/Models/Sphere.fbx");
	gameobject_scene->audio_emitter->audio_name = "BGmusic";
	
	//gameobject_scene->audio_emitter->StartSound("BGmusic");
	//gameobject_scene->CreateComponent(COMPONENT_TYPE::MESH, "Assets/Models/Street environment_V01.fbx");

	GOPath = CreateGameObject(root);
	GOPath->SetName("SourceMove");
	GOPath->CreateComponent(COMPONENT_TYPE::AUDIO_EMITTER);
	GOPath->CreateComponent(COMPONENT_TYPE::MESH, "Assets/Models/Sphere.fbx");
	GOPath->transform->position.x = 3.0f;
	GOPath->transform->position.y = 0.0f;
	GOPath->transform->position.z = 3.0f;
	GOPath->audio_emitter->audio_name = "Rain";
	//GOPath->audio_emitter->mono = true;
	//GOPath->audio_emitter->StartSound("Rain");

	reverb_zone = CreateGameObject(root);
	reverb_zone->SetName("ReverbZone");
	reverb_zone->CreateComponent(COMPONENT_TYPE::REVERB_ZONE);
	reverb_zone->reverb_zone->SetRadius(5.0f);
	reverb_zone->transform->position.z = 7.5f;
	
	camera_scene = CreateGameObject(root);
	camera_scene->CreateComponent(COMPONENT_TYPE::CAMERA);
	camera_scene->SetName("Camera");
	
	return ret;
}

update_status ModuleSceneIntro::PreUpdate(float dt)
{
	timer_in_game.UpdateTimer();
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
	GameObjects;
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



