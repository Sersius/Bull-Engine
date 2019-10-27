#ifndef __ABOUTWINDOW_H__
#define __ABOUTWINDOW_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

#include <vector>

class AboutWindow : public Window
{
public:
	AboutWindow();
	~AboutWindow();

	bool Start();
	void Draw();
	bool CleanUp();
};

#endif 