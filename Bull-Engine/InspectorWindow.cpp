#include "Application.h"
#include "Globals.h"
#include "InspectorWindow.h"
#include "ModuleLoadFBX.h"
#include "ModuleGameObject.h"
#include "ModuleWindow.h"
#include "Transform.h"
#include "Material.h"
#include "Mesh.h"
#include "Camera.h"

#include "ImGui/imgui.h"
#include "ImGuizmo/ImGuizmo.h"

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
			Guizmo(selected_go);
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
		if (selected_go->camera != nullptr) {
			if (ImGui::CollapsingHeader("Camera")) {
				ImGui::Separator();

				float near_dis = selected_go->camera->GetNear();
				if (ImGui::DragFloat("Near Plane", &near_dis, 0.1f, 0.1f, 1000.0f)) {
					selected_go->camera->SetNear(near_dis);
				}
				float far_dis = selected_go->camera->GetFar();
				if (ImGui::DragFloat("Far Plane", &far_dis, 0.1f, 25.f, 1000.0f)) {
					selected_go->camera->SetFar(far_dis);
				}
				float fov = selected_go->camera->GetFOV();
				if (ImGui::SliderFloat("Field of View", &fov, 1.0f, 179.0f)) {
					selected_go->camera->SetFOV(fov);
				}
			}
		}
	}

	ImGui::End();
}

void InspectorWindow::Guizmo(GameObject * selected)
{
	ImGuizmo::Enable(true);

	static ImGuizmo::OPERATION guizmoOperation(ImGuizmo::TRANSLATE);
	static ImGuizmo::MODE guizmoMode(ImGuizmo::WORLD);

	//Swap between guizmos mode using scancodes or uibuttons
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN) {
		guizmoOperation = ImGuizmo::TRANSLATE;
	}
	if (App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) {
		guizmoOperation = ImGuizmo::ROTATE;
	}
	if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
		guizmoOperation = ImGuizmo::SCALE;
	}
	if (ImGui::RadioButton("Translate", guizmoOperation == ImGuizmo::TRANSLATE)) {
		guizmoOperation = ImGuizmo::TRANSLATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Rotate", guizmoOperation == ImGuizmo::ROTATE)) {
		guizmoOperation = ImGuizmo::ROTATE;
	}
	ImGui::SameLine();
	if (ImGui::RadioButton("Scale", guizmoOperation == ImGuizmo::SCALE)) {
		guizmoOperation = ImGuizmo::SCALE;
	}

	ImGuiIO& io = ImGui::GetIO();
	ImGuizmo::SetRect(0, 0, io.DisplaySize.x, io.DisplaySize.y);

	float4x4 matrix = selected_go->GetComponentTransform()->GetGlobalMatrix().Transposed();
	Transform* trans = selected_go->GetComponentTransform();

	ImGuizmo::Manipulate((float*)App->camera->dummy->GetViewMatrix(), (float*)App->camera->dummy->GetProjectionMatrix(), guizmoOperation, guizmoMode, (float*)&matrix);

	if (ImGuizmo::IsUsing())
	{
		matrix = matrix.Transposed();
		selected_go->GetComponentTransform()->SetMatrixFromGlobal(matrix);
	}

}
