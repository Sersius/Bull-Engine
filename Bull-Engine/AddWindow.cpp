#include "Application.h"
#include "AddWindow.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "ModuleRenderer3D.h"
#include "ModuleSceneIntro.h"

#include "imGUI/imgui.h"
#include "ParShapes/par_shapes.h"

AddWindow::AddWindow() : Window()
{
	on = false;
}

AddWindow::~AddWindow()
{
}

bool AddWindow::Start()
{
	bool ret = true;

	return ret;
}

void AddWindow::Draw()
{
	ImGui::Begin("Enter the parameters", &on, 0);

		static int current_item = 0;
		ImGui::Combo("Select the object", &current_item, "Plane\0Cube\0Sphere\0Cone");
		
		ImGui::Text("Scale");
		ImGui::InputInt("", &scale);
		if (scale <= 0)
			scale = 1;
		ImGui::Separator();
		
		ImGui::Text("Position");
		ImGui::InputInt3("", pos);
		ImGui::Separator();
		
		ImGui::Text("Color");
		ImGui::ColorEdit3("", color);
		ImGui::Separator();

		if (current_item == 0 && ImGui::Button("Create"))
		{
			par_shapes_mesh* plane = par_shapes_create_plane(3,3);
			InfoFbx mesh = App->loadFBX->LoadParShapeMesh(plane);
			par_shapes_free_mesh(plane);	
		}

		if (current_item == 1 && ImGui::Button("Create"))
		{
			par_shapes_mesh* cube = par_shapes_create_cube();
			InfoFbx mesh = App->loadFBX->LoadParShapeMesh(cube);
			par_shapes_free_mesh(cube);
		}

		if (current_item == 2 && ImGui::Button("Create"))
		{
			par_shapes_mesh* sphere = par_shapes_create_subdivided_sphere(2);
			InfoFbx mesh = App->loadFBX->LoadParShapeMesh(sphere);
			par_shapes_free_mesh(sphere);
		}

		if (current_item == 3 && ImGui::Button("Create"))
		{
			par_shapes_mesh* cone = par_shapes_create_cone(10,10);
			InfoFbx mesh = App->loadFBX->LoadParShapeMesh(cone);
			par_shapes_free_mesh(cone);
		}
		
	ImGui::End();
}

bool AddWindow::CleanUp()
{
	return false;
}
