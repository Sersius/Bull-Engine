#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "Globals.h"
#include "SDL/include/SDL.h"

class UiMainMenu;

class ModuleUI: public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	//update_status PostUpdate(float dt);
	bool CleanUp();

public:
	UiMainMenu* mainMenu = nullptr;
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
	
};

#endif 