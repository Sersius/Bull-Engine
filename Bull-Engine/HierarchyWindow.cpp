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
		/*for (int i = 0; i < App->scene_intro->game_objects.capacity(); i++)
		{
			App->scene_intro->game_objects.at(i)->BlitHierarchy();

		}
		*/
	}

	ImGui::End();
}


