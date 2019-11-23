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
class InspectorWindow;
class SaveWindow;
class LoadWindow;
class TimeManagementWindow;
class ResourcesWindow;

class ModuleUI: public Module
{
public:
	ModuleUI(Application* app, bool start_enabled = true);
	~ModuleUI();

	
	bool Start();
	update_status PreUpdate(float dt);
	update_status Update(float dt);
	bool CleanUp();

public:
	std::vector<Window*> windows;
	ConfigWindow* config = nullptr;
	AboutWindow* about = nullptr;
	ConsoleWindow* console = nullptr;
	AddWindow* add = nullptr;
	HierarchyWindow* hierarchy = nullptr;
	InspectorWindow* inspector = nullptr;
	SaveWindow* save = nullptr;
	TimeManagementWindow* time_management = nullptr;
	LoadWindow* load = nullptr;
	ResourcesWindow* resources = nullptr;
};

#endif 