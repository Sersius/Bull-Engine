#ifndef __CONFIGWINDOW_H__
#define __CONFIGWINDOW_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

#include <vector>


class ConfigWindow : public Window
{
public:
	ConfigWindow();
	~ConfigWindow();
	

	bool Start();
	void Draw();
	bool CleanUp();

public:
	SDL_version version;
	int CPU_Cache = 0;
	int CPU_Count = 0;
	int ram = 0;
	

private:
	std::vector<float> vector_ms;
	std::vector<float> vector_fps;

};

#endif 