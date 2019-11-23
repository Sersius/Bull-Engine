#ifndef __RESOURCESWINDOW__H__
#define __RESOURCESWINDOW__H__
#include "Window.h"

#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"

#include <vector>

class ResourcesWindow : public Window
{
public:
	ResourcesWindow();
	~ResourcesWindow();

	bool Start();
	void Draw();

};

#endif
