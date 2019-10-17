#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include "ModuleComponent.h"
#include "Globals.h"
class Material : public Component
{
public:
	Material(GameObject* parent);
	~Material();

	void Update(float dt);
	void GetTexture(char* texture_path);
private:
	char* texture_path; 

};

#endif