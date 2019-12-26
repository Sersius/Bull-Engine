#ifndef __AUDIOLISTINER_H__
#define __AUDIOLISTENER_H__

#include "ModuleComponent.h"
#include "Globals.h"
#include "WwiseT.h"

class GameObject;

class AudioListener : public Component
{
public:
	AudioListener(GameObject* parent);
	~AudioListener();
	void Update(float dt);
	void UpdateListenerPos();
	void SaveListener(JSON_Array* componentsObj) const;


public:
	WwiseT::AudioSource* listener;
};

#endif // !COMCAMERA_H