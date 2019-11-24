#include "Application.h"
#include "ResourcesWindow.h"

ResourcesWindow::ResourcesWindow() : Window()
{
	on = true;
}

ResourcesWindow::~ResourcesWindow()
{
}

bool ResourcesWindow::Start()
{
	bool ret = true;

	return ret;
}

void ResourcesWindow::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	ImGui::Begin("Assets", &on, flags);

	ImGui::SetWindowPos(ImVec2(0, (App->height / 6.0f) * 4.6f), ImGuiCond_Always);
	ImGui::SetWindowSize(ImVec2(App->width / 2, (App->height / 6.0f) * 1.4f), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window, &App->width, &App->height);

	if (ImGui::TreeNodeEx("Assets"))
	{
		DrawResources(App->fileSystem->resources);
		ImGui::TreePop();
	}

	ImGui::End();
}

void ResourcesWindow::DrawResources(Directory* directory)
{
	for (uint i = 0; i < directory->dir_vec.size(); i++)
	{
		if (ImGui::TreeNodeEx(directory->dir_vec[i].name.c_str()))
		{
			DrawResources(&directory->dir_vec[i]);
			ImGui::TreePop();
		}
	}

	for (uint i = 0; i < directory->file_vec.size(); i++)
	{
		if (ImGui::TreeNodeEx(directory->file_vec[i].name.c_str(), ImGuiTreeNodeFlags_Leaf))
		{
			std::string extension;
			extension = directory->file_vec[i].name.c_str();
			uint type = extension.find_last_of(".");

			if (type != std::string::npos)
				extension = extension.substr(type);

			if (ImGui::IsMouseDoubleClicked(0) && ImGui::IsItemClicked(0) && extension.compare(".json") == 0)
				ImGui::OpenPopup("Warning!");

			ImGui::SetNextWindowSize(ImVec2(675.0f, 100.0f));
			if (ImGui::BeginPopupModal("Warning!", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove))
			{
				ImVec2 new_txt_pos(ImGui::GetWindowPos().x + 25.0f, ImGui::GetCursorScreenPos().y);
				ImGui::SetCursorScreenPos(new_txt_pos);
				ImGui::Text("The current scene will be lost if you didn't save it. Do you want to load '%s'?", directory->file_vec[i].name.c_str());

				ImGui::NewLine();
				ImVec2 new_btn_pos(ImGui::GetWindowPos().x + (675.0f / 2.0f - 100.0f / 2.0f), ImGui::GetCursorScreenPos().y);
				ImGui::SetCursorScreenPos(new_btn_pos);

				if (ImGui::Button("Load", ImVec2(50, 20)))
				{
					const char* scene = directory->file_vec[i].name.c_str();
					App->serialization->LoadScene(scene);
					ImGui::CloseCurrentPopup();
				}

				ImGui::SameLine();
				if (ImGui::Button("Cancel", ImVec2(50, 20)))
				{
					ImGui::CloseCurrentPopup();
				}

				ImGui::EndPopup();
			}

			ImGui::TreePop();
		}
	
	}
}
