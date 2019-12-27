#include "Application.h"
#include "AudioEmitter.h"
#include "Transform.h"
#include "ReverbZone.h"
#include "ModuleSceneIntro.h"
#include "ModuleAudio.h"

#define MAX(a,b) ((a)>(b)) ? (a) : (b)

ReverbZone::ReverbZone(GameObject * parent) : Component(parent, COMPONENT_TYPE::REVERB_ZONE)
{

}

ReverbZone::~ReverbZone()
{

}

void ReverbZone::Update(float dt)
{

	sphere.pos = parent->GetComponentTransform()->position;

	DebugDrawSphere();
	for (int i = 0; i < App->scene_intro->root->children.size(); ++i) {
		AudioEmitter* audio_emitter = App->scene_intro->root->children[i]->GetComponentAudioEmitter();
		if (audio_emitter != nullptr) {
			if (sphere.Intersects(App->scene_intro->root->children[i]->GetAABB()) == true) {
				audio_emitter->source->ApplyEnvReverb(12, "tunnel");
			}
			else {
				audio_emitter->source->ApplyEnvReverb(0, "tunnel");
			}
		}
	}

}

void ReverbZone::SetRadius(float rad) 
{
	radius = rad;
	sphere.r = rad;
}

void ReverbZone::DebugDrawSphere()
{
	glLineWidth(3.0f);
	glColor3f(2.0f, 2.0f, 2.0f);

	float radius = sphere.r;
	float3 pos = sphere.pos;
	float degInRad = 360.0f / 12;
	degInRad *= DEGTORAD;
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 12; i++)
		glVertex3f(cos(degInRad * i) * radius + pos.x, pos.y, sin(degInRad * i) * radius + pos.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 12; i++)
		glVertex3f(cos(degInRad * i) * radius + pos.x, sin(degInRad * i) * radius + pos.y, pos.z);
	glEnd();
	glBegin(GL_LINE_LOOP);
	for (unsigned int i = 0; i < 12; i++)
		glVertex3f(pos.x, sin(degInRad * i) * radius + pos.y, cos(degInRad * i) * radius + pos.z);
	glEnd();

	glLineWidth(1.0f);
}