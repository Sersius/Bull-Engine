#ifndef __INSPECTORWINDOW_H__
#define __INSPECTORWINDOW_H__



#include "Window.h"
#include "SDL/include/SDL.h"
#include "imGUI\imgui.h"


#include <vector>


class InspectorWindow : public Window
{
public:
	InspectorWindow();
	~InspectorWindow();


	bool Start();
	void Draw();

public:


private:


};
#endif