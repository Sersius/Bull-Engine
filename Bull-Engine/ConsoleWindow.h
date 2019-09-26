#ifndef __CONSOLEWINDOW_H__
#define __CONSOLEWINDOW_H__



#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"

#include <vector>


class ConsoleWindow : public Window
{
public:
	ConsoleWindow();
	~ConsoleWindow();


	bool Start();
	void Draw();
	bool CleanUp();

public:



private:


};
#endif