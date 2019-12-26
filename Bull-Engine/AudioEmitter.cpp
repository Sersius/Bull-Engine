#include  "AudioEmitter.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "Transform.h"
#include "MathGeoLib/include/MathGeoLib.h"

AudioEmitter::AudioEmitter(GameObject * parent) : Component(parent, COMPONENT_TYPE::AUDIO_EMITTER)
{
	source = App->audio->CreateSoundEmitter("Emitter");
	//App->audio->audio_sources.push_back(this);
	

	
}


void AudioEmitter::Update(float dt)
{
	UpdateSourcePos();
	DebugDraw();
	
	if (timer.Read() / 1000 >= time_to_swap) {
		if (song == 1) {
			source->ChangeState("swap_music", "state2");
			song = 2;
			timer.Start();
		}
		else {
			source->ChangeState("swap_music", "state1");
			song = 1;
			timer.Start();
		}
	}
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

void AudioEmitter::ChangeTimeToSwap(float new_time)
{
	time_to_swap = new_time;
}
void AudioEmitter::Mono(bool mono)
{
	this->mono = mono;
	if (mono == true)
		source->SetMono();
	else if (mono == false)
		source->SetStereo();
}

void AudioEmitter::StartSound(const char* name)
{
	source->PlayEventByName(name);
	timer.Start();
	source->SetMono();
}

void AudioEmitter::UpdateSourcePos()
{
	Transform* transformation = parent->GetComponentTransform();

	if (transformation != nullptr)
	{
		math::Quat rot = transformation->rotation;

		math::float3 vector_pos = transformation->position;

		source->SetSourcePos(vector_pos.x, vector_pos.y, vector_pos.z, 0, 0, 1, 0, 1, 0);
	}
}

