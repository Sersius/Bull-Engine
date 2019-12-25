#include  "AudioEmitter.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "Transform.h"
#include "MathGeoLib/include/MathGeoLib.h"

AudioEmitter::AudioEmitter(GameObject * parent) : Component(parent, COMPONENT_TYPE::AUDIO_EMITTER)
{
	source = App->audio->CreateSoundEmitter("Emitter");
	//App->audio->audio_sources.push_back(this);
	//timer.Start();

	
}


void AudioEmitter::Update(float dt)
{
	DebugDraw();
	

}

void AudioEmitter::DebugDraw() {

	
	cube.pos = parent->GetComponentTransform()->position;
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glBegin(GL_QUADS);
	glLineWidth(5.0f);
	glColor3f(2.0f, 2.0f, 2.0f);

	float3 vertices[8];
	cube.GetCornerPoints(vertices);

	glVertex3fv((GLfloat*)&vertices[1]);
	glVertex3fv((GLfloat*)&vertices[5]);
	glVertex3fv((GLfloat*)&vertices[7]);
	glVertex3fv((GLfloat*)&vertices[3]);

	glVertex3fv((GLfloat*)&vertices[4]);
	glVertex3fv((GLfloat*)&vertices[0]);
	glVertex3fv((GLfloat*)&vertices[2]);
	glVertex3fv((GLfloat*)&vertices[6]);

	glVertex3fv((GLfloat*)&vertices[5]);
	glVertex3fv((GLfloat*)&vertices[4]);
	glVertex3fv((GLfloat*)&vertices[6]);
	glVertex3fv((GLfloat*)&vertices[7]);

	glVertex3fv((GLfloat*)&vertices[0]);
	glVertex3fv((GLfloat*)&vertices[1]);
	glVertex3fv((GLfloat*)&vertices[3]);
	glVertex3fv((GLfloat*)&vertices[2]);

	glVertex3fv((GLfloat*)&vertices[3]);
	glVertex3fv((GLfloat*)&vertices[7]);
	glVertex3fv((GLfloat*)&vertices[6]);
	glVertex3fv((GLfloat*)&vertices[2]);

	glVertex3fv((GLfloat*)&vertices[0]);
	glVertex3fv((GLfloat*)&vertices[4]);
	glVertex3fv((GLfloat*)&vertices[5]);
	glVertex3fv((GLfloat*)&vertices[1]);

	glColor4f(1.f, 1.f, 1.f, 1.f);
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void AudioEmitter::ChangeVolume(float new_volume)
{
	volume = new_volume;
	source->SetVolume(new_volume);

}
void AudioEmitter::ChangePitch(float new_pitch)
{
	volume = new_pitch;
	source->SetPitch(new_pitch);

}

void AudioEmitter::Mute(bool mute)
{
	this->mute = mute;
	if (mute == true)
		source->SetVolume(0);
	else if (mute == false)
		source->SetVolume(volume);

}

void AudioEmitter::StartSound()
{
	source->PlayEventByName("Play");
}