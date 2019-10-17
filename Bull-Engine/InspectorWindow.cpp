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
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	if (ImGui::Begin("Inspector", &on, flags)) {

		ImGui::SetWindowPos(ImVec2((App->width / 4) * 3, 20), ImGuiCond_Always);
		ImGui::SetWindowSize(ImVec2(App->width / 4, 795), ImGuiCond_Always);
		SDL_GetWindowSize(App->window->window, &App->width, &App->height);

		ImGui::Text("Model Name: %s");
		ImGui::Text("Model Path: %s");

		if (ImGui::CollapsingHeader("Transform")) {
			ImGui::Separator();

			ImGui::Text("Position:");
			ImGui::Text("[%f]    [%f]    [%f]");

			ImGui::Text("Rotation:");
			ImGui::Text("[%f]    [%f]    [%f]");

			ImGui::Text("Scale:");
			ImGui::Text("[%f]    [%f]    [%f]");
		}

		if (ImGui::CollapsingHeader("Mesh Information")) {
			ImGui::Separator();

			ImGui::Text("Mesh triangles: %i");

			ImGui::Text("Mesh vertices: %i");

			ImGui::Text("Mesh indices: %i");

			ImGui::Text("Mesh normals: %f");

			ImGui::Text("Mesh uvs: %f");
		}

		if (ImGui::CollapsingHeader("Material")) {
			ImGui::Separator();

			ImGui::Text("Texture path: %s");

			ImGui::Text("Texture WIDTH: %i");

			ImGui::Text("Texture HEIGHT: %i");
		}
	
	}

	ImGui::End();
}