#include "Application.h"
#include "InspectorWindow.h"
#include "ModuleLoadFBX.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

#include "Transform.h"

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
	ImGui::Begin("Inspector", &on, flags);

		ImGui::SetWindowPos(ImVec2((App->width / 4) * 3, 20), ImGuiCond_Once);
		ImGui::SetWindowSize(ImVec2(App->width / 4, 795), ImGuiCond_Once);
		SDL_GetWindowSize(App->window->window, &App->width, &App->height);

		ImGui::Text("Model Name: %s", App->loadFBX->file_name.c_str());
		ImGui::Text("Model Path: %s", App->loadFBX->path.c_str());

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

			ImGui::Text("Texture path: %s", App->loadFBX->texture_path.c_str());

			ImGui::Text("Texture WIDTH: %i", App->loadFBX->texture_width);

			ImGui::Text("Texture HEIGHT: %i", App->loadFBX->texture_height);
		}


	ImGui::End();
}