#ifndef __AUDIOEMITTER_H__
#define __AUDIOEMITTER_H__

#include "ModuleComponent.h"
#include "Globals.h"
#include "WwiseT.h"

class AudioEmitter : public Component
{
public:
	AudioEmitter(GameObject* parent);
	~AudioEmitter();
public:

	void Update(float dt);
	void ChangeVolume(float new_volume);
	void DebugDraw();

public:
	WwiseT::AudioSource* source;
	math::OBB cube;
	float volume = 1.0f;

	
	

};

#endif