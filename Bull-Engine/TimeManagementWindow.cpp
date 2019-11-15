#include "Application.h"
#include "TimeManagementWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI/imgui.h"

TimeManagementWindow::TimeManagementWindow() : Window()
{
	on = true;

}

TimeManagementWindow::~TimeManagementWindow()
{
}

bool TimeManagementWindow::Start()
{
	bool ret = true;

	return ret;
}





void TimeManagementWindow::Draw()
{
	ImGui::Begin("Time Manager", &on, ImGuiWindowFlags_NoTitleBar);
	if (ImGui::Button("Play"))
	{
		App->scene_intro->game_running = true;
	}
	ImGui::SameLine();
	/*if (App->scene_intro->in_game_timer.IsPaused() == false) {
		if (ImGui::Button("Pause"))
		{
		
		}
	}
	else {
		if (ImGui::Button("Continue"))
		{
		
		}
	}*/
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		App->scene_intro->game_running = false;
	}

	ImGui::End();
}


