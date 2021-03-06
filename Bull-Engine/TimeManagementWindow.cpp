#include "Application.h"
#include "TimeManagementWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "AudioEmitter.h"
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
	ImGui::Begin("Time Manager", &on,ImGuiWindowFlags_HorizontalScrollbar |ImGuiWindowFlags_NoMove |ImGuiWindowFlags_NoTitleBar |ImGuiWindowFlags_NoResize |ImGuiWindowFlags_NoCollapse);

	ImGui::SetWindowPos(ImVec2((App->width / 8.0f) * 1.5f, 18.0f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2((App->width / 8.0f) * 4.5f, 60), ImGuiCond_Always);

	
	if (ImGui::Button("Play"))
	{
		LOG("Game Mode ON");
		App->serialization->SaveScene("Autosave");
		App->scene_intro->game_running = true;
		/*if (App->scene_intro->gameobject_scene->audio_emitter != nullptr)
			App->scene_intro->gameobject_scene->audio_emitter->StartSound("BGmusic");
		if (App->scene_intro->GOPath->audio_emitter != nullptr) 
			App->scene_intro->GOPath->audio_emitter->StartSound("Rain");*/
		if(App->audio->is_playing == false)
			App->audio->Play();
		
		
	}
	ImGui::SameLine();
	if (App->scene_intro->timer_in_game.paused == false) {
		if (ImGui::Button("Pause"))
		{
			LOG("Game Mode PAUSED");
			App->scene_intro->timer_in_game.paused = true;
			App->scene_intro->timer_in_game.time = App->scene_intro->timer_in_game.time;
			/*App->scene_intro->gameobject_scene->audio_emitter->source->PauseEventByName("BGmusic");
			App->scene_intro->gameobject_scene->audio_emitter->source->PauseEventByName("Rain");*/
			App->audio->Pause();
		}
	}
	
	else{
		if (ImGui::Button("Continue"))
		{
			LOG("Game Mode STOPPED");
			App->scene_intro->timer_in_game.paused = false;
			/*if (App->scene_intro->gameobject_scene->audio_emitter != nullptr)
				App->scene_intro->gameobject_scene->audio_emitter->source->ResumeEventByName("BGmusic");
			if (App->scene_intro->GOPath->audio_emitter != nullptr)
				App->scene_intro->GOPath->audio_emitter->source->ResumeEventByName("Rain");*/
			App->audio->Resume();
		}
	}
	ImGui::SameLine();
	if (ImGui::Button("Stop"))
	{
		LOG("Game Mode OFF");
		App->scene_intro->game_running = false;
		App->serialization->LoadScene("Autosave");
		App->renderer3D->RecalculateProjectionMatrix();
		App->scene_intro->gameobject_scene->audio_emitter = nullptr;
		App->scene_intro->GOPath->audio_emitter = nullptr;

		if (App->audio->is_playing == true)
			App->audio->Stop();
	}
	ImGui::SameLine();
	if (App->scene_intro->game_running == true) {
		if (ImGui::Button("Change camera"))
		{
			App->renderer3D->editor_camera_in_game = !App->renderer3D->editor_camera_in_game;
		}
	}
	ImGui::SameLine();
	char gameTime[20] = "";
	sprintf_s(gameTime, sizeof(gameTime), "%.3f", App->scene_intro->timer_in_game.time);
	ImGui::Text(gameTime);
	if (ImGui::SliderFloat("TimeScale", &TimeScale, 0.0f, 2.0f))
	{
		App->scene_intro->timer_in_game.time_scale = TimeScale;
	}
	

	ImGui::End();
}


