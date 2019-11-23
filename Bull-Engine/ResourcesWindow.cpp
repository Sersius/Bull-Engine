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

	ImGui::End();
}
