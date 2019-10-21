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
	
	ImGui::SetWindowPos(ImVec2((App->width / 3.0f) * 2, 20), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(App->width / 3.0f, 795), ImGuiCond_Once);
	SDL_GetWindowSize(App->window->window, &App->width, &App->height);

	
	GameObject* selected_go = App->scene_intro->GetSelectedGO();
	
	if (selected_go != nullptr) {
		LOG("%s", selected_go->GetName());
		ImGui::Text("Model Name: %s", App->loadFBX->file_name.c_str());
		ImGui::Text("Model Path: %s", App->loadFBX->path.c_str());
		if (ImGui::CollapsingHeader("Transform")) {
			ImGui::Separator();

			ImGui::Text("Position:");
			ImGui::Text("[%f]    [%f]    [%f]", App->loadFBX->mesh.position.x, App->loadFBX->mesh.position.y, App->loadFBX->mesh.position.z);

			ImGui::Text("Rotation:");
			ImGui::Text("[%f]    [%f]    [%f]", App->loadFBX->mesh.rotation.x, App->loadFBX->mesh.rotation.y, App->loadFBX->mesh.rotation.z);

			ImGui::Text("Scale:");
			ImGui::Text("[%f]    [%f]    [%f]", App->loadFBX->mesh.scale.x, App->loadFBX->mesh.scale.y, App->loadFBX->mesh.scale.z);
		}

		if (ImGui::CollapsingHeader("Mesh Information")) {
			ImGui::Separator();

			ImGui::Text("Mesh triangles: %i", App->loadFBX->mesh.num_vertex / 3);

			ImGui::Text("Mesh vertices: %i", App->loadFBX->mesh.num_vertex);

			ImGui::Text("Mesh indices: %i", App->loadFBX->mesh.num_index);

			ImGui::Text("Mesh normals: %f", App->loadFBX->mesh.num_normals);

			ImGui::Text("Mesh uvs: %f", App->loadFBX->mesh.num_uvs);
		}

		if (ImGui::CollapsingHeader("Material")) {
			ImGui::Separator();

			ImGui::Text("Texture path: %s", App->loadFBX->texture_path.c_str());

			ImGui::Text("Texture WIDTH: %i", App->loadFBX->texture_width);

			ImGui::Text("Texture HEIGHT: %i", App->loadFBX->texture_height);

			if (App->loadFBX->texture_id == 0) {
				ImGui::Image((ImTextureID)App->loadFBX->texture_id, ImVec2(200, 200));
			}
			else {
				ImGui::Image((ImTextureID)App->loadFBX->texture_id, ImVec2(200, 200));
			}
		}
	}

	ImGui::End();
}