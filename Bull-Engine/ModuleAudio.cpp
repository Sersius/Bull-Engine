#include "Globals.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "AudioEmitter.h"

ModuleAudio::ModuleAudio(Application* app, bool start_enabled) : Module(app, start_enabled)
{}

ModuleAudio::~ModuleAudio()
{}

bool ModuleAudio::Start()
{
	// Init wwise and audio banks
	WwiseT::InitSoundEngine();
	WwiseT::LoadBank("Assignment3.bnk");
	
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
	
	std::list<AudioEmitter*>::const_iterator iterator;
	for (iterator = audios.begin(); iterator != App->audio->audios.end(); ++iterator)
	{
		
			iterator._Ptr->_Myval->StartSound("BGmusic");
			iterator._Ptr->_Myval->StartSound("Rain");
		
	}
}

void ModuleAudio::Stop() const
{
	std::list<AudioEmitter*>::const_iterator iterator;
	for (iterator = audios.begin(); iterator != App->audio->audios.end(); ++iterator)
	{

		iterator._Ptr->_Myval->source->StopEventByName("BGmusic");
		iterator._Ptr->_Myval->source->StopEventByName("Rain");

	}
}

void ModuleAudio::Pause() const
{
	std::list<AudioEmitter*>::const_iterator iterator;
	for (iterator = audios.begin(); iterator != App->audio->audios.end(); ++iterator)
	{

		iterator._Ptr->_Myval->source->PauseEventByName("BGmusic");
		iterator._Ptr->_Myval->source->PauseEventByName("Rain");

	}
}

void ModuleAudio::Resume() const
{
	std::list<AudioEmitter*>::const_iterator iterator;
	for (iterator = audios.begin(); iterator != App->audio->audios.end(); ++iterator)
	{

		iterator._Ptr->_Myval->source->ResumeEventByName("BGmusic");
		iterator._Ptr->_Myval->source->ResumeEventByName("Rain");

	}
}

void ModuleAudio::SetListener(WwiseT::AudioSource* new_listener)
{
	listener = new_listener;
	WwiseT::SetDefaultListener(new_listener->GetID());
}

