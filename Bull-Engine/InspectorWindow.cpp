#include "Application.h"
#include "InspectorWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

InspectorWindow::InspectorWindow() : Window()
{
	on = true;

}

InspectorWindow::~InspectorWindow()
{
}

bool InspectorWindow::Start()
{
	bool ret = true;

	return ret;
}

void InspectorWindow::Draw()
{
	if (ImGui::Begin("Hierarchy", &on, 0)) {

	}

	ImGui::End();
}