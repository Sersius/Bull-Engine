#include "Application.h"
#include "LoadWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"

#include "imGUI/imgui.h"

LoadWindow::LoadWindow() : Window()
{
	on = false;

}

LoadWindow::~LoadWindow()
{
}

bool LoadWindow::Start()
{
	bool ret = true;

	return ret;
}

void LoadWindow::Draw()
{
	ImGui::OpenPopup("Some Popup");

	if (ImGui::BeginPopup("Some Popup"))
	{
		ImGui::SetWindowSize(ImVec2(370, 795), ImGuiCond_Always);
		//SDL_GetWindowSize(App->window->window, &App->width, &App->height);
		ImGui::SetWindowPos(ImVec2(App->width / 3 + 40, 100), ImGuiCond_Always);
		ImGui::Text("Enter the name of the scene:");

		ImGui::Separator();
		static char file_name[100] = "";
		ImGui::InputText("##name", file_name, 100);
		if (ImGui::Button("Load"))
		{
			App->serialization->LoadScene(file_name);
			on = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::SameLine();
		if (ImGui::Button("Cancel"))
		{
			on = false;
			ImGui::CloseCurrentPopup();
		}
		ImGui::EndPopup();
	}
}

//ImGui::End();
