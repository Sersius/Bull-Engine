#ifndef __LOADWINDOW_H__
#define __LOADWINDOW_H__
#include "Window.h"

#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>


class LoadWindow : public Window
{
public:
	LoadWindow();
	~LoadWindow();

	bool Start();
	void Draw();

public:


private:


};
#endif