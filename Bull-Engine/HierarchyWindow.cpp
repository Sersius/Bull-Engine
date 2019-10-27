#include "Application.h"
#include "HierarchyWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

HierarchyWindow::HierarchyWindow() : Window()
{
	on = true;

}

HierarchyWindow::~HierarchyWindow()
{
}

bool HierarchyWindow::Start()
{
	bool ret = true;

	return ret;
}





void HierarchyWindow::Draw()
{

	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;

	if (ImGui::Begin("Hierarchy", &on, flags)) {

		ImGui::SetWindowPos(ImVec2(0.1f, 18.0f), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2((App->width / 8.0f) * 1.5f, (App->height / 6.0f) * 4.5f), ImGuiCond_Always);
		SDL_GetWindowSize(App->window->window, &App->width, &App->height);

		if (App->scene_intro->root != nullptr) {
			App->scene_intro->root->BlitHierarchy(App->scene_intro->root);

		}
	}

	ImGui::End();
}


