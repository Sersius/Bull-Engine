#ifndef __SAVEWINDOW_H__
#define __SAVEWINDOW_H__
#include "Window.h"

#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>


class SaveWindow : public Window
{
public:
	SaveWindow();
	~SaveWindow();

	bool Start();
	void Draw();

public:
	

private:


};
#endif