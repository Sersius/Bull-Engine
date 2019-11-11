#include "Application.h"
#include "Globals.h"
#include "InspectorWindow.h"
#include "ModuleLoadFBX.h"
#include "ModuleGameObject.h"
#include "ModuleWindow.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"

#include "imGUI/imgui.h"

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
	
	ImGui::SetWindowPos(ImVec2((App->width / 8.0f) * 6.0f, 18), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2((App->width / 8.0f) * 2.0f, (App->height / 6.0f) * 4.5f), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->width, &App->height);

	selected_go = App->scene_intro->GetSelectedGO();
	
	if (selected_go != nullptr) {
		
		ImGui::Text("Model Name: %s", selected_go->GetName());
		ImGui::Text("Model Path: %s", App->loadFBX->path.c_str());
		
		if (selected_go->transform != nullptr) {
			if (ImGui::CollapsingHeader("Transform")) {
				ImGui::Separator();

				//ImGui::Text("Position:");
				if (ImGui::DragFloat3("Position", &selected_go->transform->position[0], 0.1f, 0.0f, 0.0f, "%.2f"))
				{
					selected_go->transform->SetPosition(selected_go->transform->position);
					selected_go->BoundingBox();
				}
				
				//ImGui::Text("Rotation:");
				float3 NewRotation = selected_go->transform->rotation.ToEulerXYZ();
				NewRotation = (NewRotation * RADTODEG);
				if (ImGui::DragFloat3("Rotation", &NewRotation[0], 0.1f, 0.0f, 0.0f, "%.2f"))
				{
					selected_go->transform->SetRotation(NewRotation);
					selected_go->BoundingBox();
				}

				//ImGui::Text("Scale:");
				if (ImGui::DragFloat3("Scale", &selected_go->transform->scale[0], 0.1f, 0.0f, 0.0f, "%.2f"))
				{

				}
			}
		}
		if (selected_go->mesh != nullptr) {
			if (ImGui::CollapsingHeader("Mesh Information")) {
				ImGui::Separator();
				ImGui::Checkbox("Render model", &selected_go->render_model);
				if (selected_go->mesh->info_mesh.num_uvs > 0) {
					ImGui::Checkbox("Draw normals", &selected_go->mesh->draw_normals);
				}
				ImGui::Text("Mesh triangles: %i", selected_go->mesh->info_mesh.num_vertex / 3);

				ImGui::Text("Mesh vertices: %i", selected_go->mesh->info_mesh.num_vertex);

				ImGui::Text("Mesh indices: %i", selected_go->mesh->info_mesh.num_index);

				ImGui::Text("Mesh normals: %i", selected_go->mesh->info_mesh.num_normals);

				ImGui::Text("Mesh uvs: %i", selected_go->mesh->info_mesh.num_uvs);
			}
		}
		if (selected_go->material != nullptr && selected_go->is_primitive == false) {
			if (ImGui::CollapsingHeader("Material")) {
				ImGui::Separator();

				ImGui::Checkbox("Texture", &selected_go->material->draw_texture);
				ImGui::SameLine();
				ImGui::Checkbox("Checkers", &selected_go->material->draw_checkers);
				ImGui::Text("Texture path: %s", App->loadFBX->texture_path.c_str());

				ImGui::Text("Texture WIDTH: %i", App->loadFBX->texture_width);

				ImGui::Text("Texture HEIGHT: %i", App->loadFBX->texture_height);

				if (App->loadFBX->texture_id == 0) {
					ImGui::Image((ImTextureID)selected_go->material->id, ImVec2(200, 200));
				}
				else {
					ImGui::Image((ImTextureID)selected_go->material->id, ImVec2(200, 200));
				}
			}
		}
	}

	ImGui::End();
}