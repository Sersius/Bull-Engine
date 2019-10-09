#ifndef __ADDWINDOW_H__
#define __ADDWINDOW_H__

#include "Module.h"
#include "Application.h"	
#include "Globals.h"
#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

#include <vector>


class AddWindow : public Window
{
public:
	AddWindow();
	~AddWindow();


	bool Start();
	void Draw();
	bool CleanUp();

public:



private:


};

#endif 
