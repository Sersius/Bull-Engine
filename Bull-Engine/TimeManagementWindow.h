#ifndef __TIMEMANAGEMENTWINDOW_H__
#define __TIMEMANAGEMENTWINDOW_H__

#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"

#include <vector>

class TimeManagementWindow : public Window
{
public:
	TimeManagementWindow();
	~TimeManagementWindow();

	bool Start();
	void Draw();

};
#endif