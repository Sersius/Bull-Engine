#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"

ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Start()
{
	// Init wwise and audio banks
	WwiseT::InitSoundEngine();
	WwiseT::LoadBank("New_SoundBank.bnk");
	
	//source = App->audio->CreateSoundEmitter("Emitter");
	//SetListener(source);

	return true;
}

update_status ModuleAudio::Update(float dt)
{
	
	return UPDATE_CONTINUE;
}

update_status ModuleAudio::PostUpdate(float dt)
{
	WwiseT::ProcessAudio();
	return UPDATE_CONTINUE;
}

bool ModuleAudio::CleanUp()
{
	//audio_sources.clear();
	//event_list.clear();
	return true;
}

WwiseT::AudioSource * ModuleAudio::CreateSoundEmitter(const char * name)
{
	WwiseT::AudioSource* ret = WwiseT::CreateAudSource(name);
	//event_list.push_back(ret);
	return ret;
}

uint ModuleAudio::GetListenerID() const
{
	return listener->GetID();
}

void ModuleAudio::PlayOnAwake() const
{
	//source.
	/*std::list<CompAudioSource*>::const_iterator iterator;
	for (iterator = App->audio->audio_sources.begin(); iterator != App->audio->audio_sources.end(); ++iterator)
	{
		if (iterator._Ptr->_Myval->GetPlayOnAwake() == true)
		{
			iterator._Ptr->_Myval->PlayAudio();
		}
	}*/
}

void ModuleAudio::Stop() const
{
	WwiseT::StopAllEvents();
}

void ModuleAudio::Pause() const
{
	WwiseT::PauseAll();
}

void ModuleAudio::Resume() const
{
	WwiseT::ResumeAll();
}

void ModuleAudio::SetListener(WwiseT::AudioSource* new_listener)
{
	listener = new_listener;
	WwiseT::SetDefaultListener(new_listener->GetID());
}

