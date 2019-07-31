#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "imGUI\imgui.h"
#include "imGUI\imgui_impl_sdl_gl3.h"
#include "Glew\include\glew.h"

#pragma comment( lib, "Glew/libx86/glew32.lib" )



ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;
	glewInit();
	//HARDWARE
	
	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	return ret;
}
update_status ModuleSceneIntro::PreUpdate(float dt)
{
	return(UPDATE_CONTINUE);
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = true;
	p.Render();
	//static bool show_test_window = false;
	//static int sliderInt = 0;
	//static float sliderFloat = 0.0f;
	//static bool show_app_main_menu_bar = false;
	////ImGui::PushItemWidth(ImGui::GetFontSize() * 12);
	//if (show_test_window)
	//{
	//	
	//	ImGui::ShowTestWindow();
	//}
	//	ImGui::Begin("ImGui Test");
	//	ImGui::Text("SDL Version: ");
	//	ImGui::SameLine();
	//	ImGui::Text("%d.%d.%d", version.major, version.minor, version.patch);
	//	ImGui::Separator();
	//	ImGui::Text("CPUs: ");
	//	ImGui::SameLine();
	//	ImGui::Text("%i (Cache:%ikb)", CPU_Count,CPU_Cache);
	//	ImGui::Text("System RAM: %iGb ",ram);
	//
	//	ImGui::Text("Caps: ");
	//	ImGui::Separator();
	//	ImGui::Text("GPU: ");
	//	ImGui::Text("Brand: ");
	//	ImGui::Text("VRAM Budget: ");
	//	ImGui::Text("VRAM Usage: ");
	//	ImGui::Text("VRAM Available: ");
	//	ImGui::Text("VRAM Reserved: ");
	//	ImGui::SliderInt("Slider", &sliderInt, 0, 100);
	//	ImGui::SliderFloat("SliderFloat", &sliderFloat, 0.0f, 100.0f);
	//	ImGui::Separator();
	//	ImGui::Spacing();
	//	ImGui::ColorEdit3("clear color", (float*)&clear_color);
	//	ImGui::End();
	//		
	//
	//if (ImGui::BeginMenu("Examples"))
	//{
	//	ImGui::MenuItem("Main menu bar", NULL, &show_app_main_menu_bar);
	//	ImGui::SameLine(); //HelpMarker("Set to false to disable blinking cursor, for users who consider it distracting");
	//	ImGui::EndMenu();
	//}
	//if (ImGui::CollapsingHeader("Help"))
	//{
	//	ImGui::Text("PROGRAMMER GUIDE:");
	//	ImGui::ShowUserGuide();
	//}
	//if (ImGui::TreeNode("Style"))
	//{
	//	ImGui::ShowStyleEditor();
	//	ImGui::TreePop();
	//	ImGui::Separator();
	//}
	//if (ImGui::TreeNode("Capture/Logging"))
	//{
	//	ImGui::TextWrapped("The logging API redirects all text output so you can easily capture the content of a window or a block. Tree nodes can be automatically expanded.");
	//	//HelpMarker("Try opening any of the contents below in this window and then click one of the \"Log To\" button.");
	//	ImGui::LogButtons();
	//	ImGui::TextWrapped("You can also call ImGui::LogText() to output directly to the log without a visual output.");
	//	if (ImGui::Button("Copy \"Hello, world!\" to clipboard"))
	//	{
	//		ImGui::LogToClipboard();
	//		ImGui::LogText("Hello, world!");
	//		ImGui::LogFinish();
	//	}
	//	ImGui::TreePop();
	//}
	//static int e = 0;
	//ImGui::RadioButton("radio a", &e, 0); ImGui::SameLine();
	//ImGui::RadioButton("radio b", &e, 1); ImGui::SameLine();
	//ImGui::RadioButton("radio c", &e, 2);
	//for (int i = 0; i < 7; i++)
	//{
	//	if (i > 0)
	//		ImGui::SameLine();
	//	ImGui::PushID(i);
	//	ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(i / 7.0f, 0.6f, 0.6f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(i / 7.0f, 0.7f, 0.7f));
	//	ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(i / 7.0f, 0.8f, 0.8f));
	//	ImGui::Button("Click");
	//	ImGui::PopStyleColor(3);
	//	ImGui::PopID();
	//}

	//if (ImGui::BeginMainMenuBar())
	//{
	//	if (ImGui::BeginMenu("File"))
	//	{
	//		if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
	//		if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
	//		
	//		ImGui::EndMenu();
	//	}
	//	ImGui::EndMainMenuBar();
	//
	//}
	//ImGui::Render();
	



	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

