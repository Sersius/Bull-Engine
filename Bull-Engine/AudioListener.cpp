#include "AudioListener.h"
#include "Application.h"
#include "ModuleAudio.h"
#include  "Transform.h"
#include "MathGeoLib\include\MathGeoLib.h"

AudioListener::AudioListener(GameObject * parent) : Component(parent, COMPONENT_TYPE::AUDIO_EMITTER)
{
	listener = App->audio->CreateSoundEmitter("listener");
	App->audio->SetListener(listener);
}

AudioListener::~AudioListener()
{
	//RELEASE(listener);
}

void AudioListener::Update(float dt)
{

}

void AudioListener::UpdateListenerPos()
{
	
}