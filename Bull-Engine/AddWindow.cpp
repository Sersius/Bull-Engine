#include "Application.h"
#include "AddWindow.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

AddWindow::AddWindow() : Window()
{
	on = false;
}

AddWindow::~AddWindow()
{
}

bool AddWindow::Start()
{
	bool ret = true;

	return ret;
}

void AddWindow::Draw()
{
	ImGui::Begin("Enter the parameters", &on, 0);
	ImGui::Text("Bull Engine v0.3");
	ImGui::End();
}

bool AddWindow::CleanUp()
{
	return false;
}
