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
		App->serialization->SaveScene("Autosave");
		App->scene_intro->game_running = true;
		
	}
	ImGui::SameLine();
	if (App->scene_intro->timer_in_game.paused == false) {
		if (ImGui::Button("Pause"))
		{
			App->scene_intro->timer_in_game.paused = true;
		}
	}
	
	else{
		if (ImGui::Button("Continue"))
		{
			App->scene_intro->timer_in_game.paused = false;
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		App->scene_intro->game_running = false;
		App->serialization->LoadScene("Autosave");
	}

	if (App->scene_intro->game_running == true) {
		if (ImGui::Button("Change camera"))
		{
			App->renderer3D->editor_camera_in_game = !App->renderer3D->editor_camera_in_game;
		}
	}
	if (ImGui::SliderFloat("TimeScale", &TimeScale, 0.0f, 2.0f))
	{
		App->scene_intro->timer_in_game.time_scale = TimeScale;
	}
	char gameTime[20] = "";
	sprintf_s(gameTime, sizeof(gameTime), "%.3f", App->scene_intro->timer_in_game.time);
	ImGui::Text(gameTime);

	ImGui::End();
}


