#ifndef __ModuleUI_H__
#define __ModuleUI_H__

#include "Module.h"
#include "Globals.h"
#include "Window.h"
#include "SDL/include/SDL.h"
#include <vector>

class Window;
class ConfigWindow;
class AboutWindow;
class ConsoleWindow;
class AddWindow;
class HierarchyWindow;

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
	std::vector<Window*> windows;
	ConfigWindow* config = nullptr;
	AboutWindow* about = nullptr;
	ConsoleWindow* console = nullptr;
	AddWindow* add = nullptr;
	HierarchyWindow* hierarchy = nullptr;

private:
	
};

#endif 