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
	static int current_item = 0;
	ImGui::Combo("Select the object", &current_item, "Plane\0Pyramid\0Cube");

	ImGui::Text("Scale");
	ImGui::InputInt("", &scale);
	if (scale <= 0)
		scale = 1;
	ImGui::Separator();

	ImGui::Text("Position");
	ImGui::InputInt3("", pos);
	ImGui::Separator();

	ImGui::Text("Color");
	ImGui::ColorEdit3("", color);
	ImGui::Separator();

	if (ImGui::Button("Create") == true || current_item == 0)
		ImGui::Text("XD");

	else if (ImGui::Button("Create") == true || current_item == 1)
		ImGui::Text("XD");

	else if (ImGui::Button("Create") == true || current_item == 2)
		ImGui::Text("XD");

	ImGui::End();
}

bool AddWindow::CleanUp()
{
	return false;
}
