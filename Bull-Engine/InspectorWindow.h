#ifndef __INSPECTORWINDOW_H__
#define __INSPECTORWINDOW_H__
#include "Window.h"

#include "SDL/include/SDL.h"
#include "imGUI/imgui.h"
#include "MathGeoLib/include/MathGeoLib.h"

#include <vector>


class InspectorWindow : public Window
{
public:
	InspectorWindow();
	~InspectorWindow();

	bool Start();
	void Draw();

	void Guizmo(GameObject* selected_go);

public:
	GameObject* selected_go = nullptr;

private:


};
#endif