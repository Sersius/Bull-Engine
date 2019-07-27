#include "Globals.h"
#include "Application.h"
#include "ModuleUI.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"





ModuleUI ::ModuleUI(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleUI::~ModuleUI()
{}

bool ModuleUI::Start()
{
	bool ret = true;
	ImGui_ImplSdlGL3_Init(App->window->window);
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
	
	//ImGui::ShowTestWindow();
	static bool show_test = false;
	if (show_test)
		ImGui::ShowTestWindow();
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
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
	if (ImGui::Begin("HOLA")) {
		ImGui::Text("AAAAA");
		ImGui::ColorEdit3("clear color", (float*)&clear_color);
		//ImGui::PushStyleColor(ImGuiCol_WindowBg, (ImVec4)ImColor::HSV(clear_color.x, clear_color.y, clear_color.w, clear_color.z));
	}
	ImGui::End();
	ImGui::Render();
	return UPDATE_CONTINUE;
}
