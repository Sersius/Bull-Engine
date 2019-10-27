#ifndef __HIERARCHYWINDOW_H__
#define __HIERARCHYWINDOW_H__

#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"

#include <vector>

class HierarchyWindow : public Window
{
public:
	HierarchyWindow();
	~HierarchyWindow();
	
	bool Start();
	void Draw();
	
};
#endif