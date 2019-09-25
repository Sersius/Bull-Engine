#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "Module.h"
#include "ConfigWindow.h"
#include "AboutWindow.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

ModuleUI ::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	bool ret = true;
	
	ImGui_ImplSdlGL3_Init(App->window->window);
	windows.push_back(config = new ConfigWindow());
	windows.push_back(about = new AboutWindow());
	return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplSdlGL3_NewFrame(App->window->window);
	
	return(UPDATE_CONTINUE);
}


bool ModuleUI::CleanUp()
{
	ImGui_ImplSdlGL3_Shutdown();
	return true;
}

update_status ModuleUI::Update(float dt)
{
	static bool show_test = false;
	if (show_test)
		ImGui::ShowTestWindow();

	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("Menu"))
		{
			if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
			if (ImGui::MenuItem("Save", "Ctrl+S")) { show_test = true; }
			if (ImGui::MenuItem("Quit", "Alt+F4"))
			{
				return UPDATE_STOP;
			}

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	for (int i = 0; i < windows.capacity(); i++)
	{
		if (windows[i]->on == true)
			windows[i]->Draw();
	}
	ImGui::End();
	ImGui::Render();
	
	return UPDATE_CONTINUE;
}
