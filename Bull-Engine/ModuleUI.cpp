#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "Module.h"
#include "ConfigWindow.h"
#include "AboutWindow.h"
#include "ConsoleWindow.h"
#include "AddWindow.h"
#include "HierarchyWindow.h"
#include "InspectorWindow.h"

#include "imGUI\imgui.h"
#include "ImGui/imgui_impl_opengl3.h"
#include "ImGui/imgui_impl_sdl.h"
#include "ImGui\imgui_internal.h"
#include "Psapi.h"
#include "MathGeoLib/include/MathGeoLib.h"
#include "Glew\include\glew.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )

ModuleUI ::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	windows.push_back(config = new ConfigWindow());
	windows.push_back(about = new AboutWindow());
	windows.push_back(console = new ConsoleWindow());
	windows.push_back(add = new AddWindow());
	windows.push_back(hierarchy = new HierarchyWindow());
	windows.push_back(inspector = new InspectorWindow());
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	bool ret = true;
	
	config->Start();
	return ret;
}

update_status ModuleUI::PreUpdate(float dt)
{
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame(App->window->window);
	ImGui::NewFrame();
	
	return(UPDATE_CONTINUE);
}


bool ModuleUI::CleanUp()
{
	for (int i = 0; i < windows.capacity()-1; i++)
	{
		windows[i]->~Window();
	}
	windows.clear();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
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
			if (ImGui::MenuItem("Save","Coming soon")) {}
			if (ImGui::MenuItem("Load", "Coming soon")) {}
			ImGui::Separator();
			if (ImGui::MenuItem("Exit", "Escape")) { return UPDATE_STOP; }
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Window"))
		{
			if (ImGui::MenuItem("Configuration")) { config->on = !config->on; }
			if (ImGui::MenuItem("Inspector")) { inspector->on = !inspector->on; }
	
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			ImGui::Checkbox("Console",&console->on);
			ImGui::Separator();
			ImGui::Checkbox("Wireframe mode", &App->renderer3D->wireframe);
			//TODO:: DEPTH CULL MODE, etc...
			ImGui::EndMenu();
		}
		
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("GUI Demo")) { show_test = !show_test; }
			if (ImGui::MenuItem("About")) { about->on = !about->on; }			

			ImGui::EndMenu();
		}

		if (ImGui::BeginMenu("Add an object"))
		{
			add->on = !add->on;

			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	for (int i = 0; i < windows.capacity()-1; i++)
	{
		if (windows[i]->IsActivated())
			windows[i]->Draw();
	}
	
	ImGui::Render();
	
	return UPDATE_CONTINUE;
}
