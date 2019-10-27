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
	GameObject* new_go;


private:
	int scale = 1;
	int pos[3] = { 1, 1, 1 };
	float color[3] = { 1.0f, 1.0f, 1.0f };

};

#endif 
