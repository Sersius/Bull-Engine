#include "Application.h"
#include "HierarchyWindow.h"
#include "ModuleGameObject.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

HierarchyWindow::HierarchyWindow() : Window()
{
	on = true;

}

HierarchyWindow::~HierarchyWindow()
{
}

bool HierarchyWindow::Start()
{
	bool ret = true;

	return ret;
}





void HierarchyWindow::Draw()
{
	if (ImGui::Begin("Hierarchy", &on, 0)) {
		if (App->scene_intro->root != nullptr) {
			App->scene_intro->root->BlitHierarchy(App->scene_intro->root);
		}
		
	}

	ImGui::End();
}


