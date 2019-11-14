#ifndef __SAVELOADWINDOW_H__
#define __SAVELOADWINDOW_H__
#include "Window.h"

#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>


class SaveLoadWindow : public Window
{
public:
	SaveLoadWindow();
	~SaveLoadWindow();

	bool Start();
	void Draw();

public:
	//GameObject* selected_go = nullptr;

private:


};
#endif