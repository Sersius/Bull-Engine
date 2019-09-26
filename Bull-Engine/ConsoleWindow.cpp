#include "Application.h"
#include "ConsoleWindow.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

ConsoleWindow::ConsoleWindow() : Window()
{
	on = true;
}

ConsoleWindow::~ConsoleWindow()
{
}

bool ConsoleWindow::Start()
{
	bool ret = true;

	return ret;
}

void ConsoleWindow::Draw()
{
	ImGui::Begin("Console", &on, 0);
	ImGui::End();
}

bool ConsoleWindow::CleanUp()
{
	return false;
}