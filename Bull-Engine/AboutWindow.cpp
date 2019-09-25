#include "Application.h"
#include "AboutWindow.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

AboutWindow::AboutWindow() : Window()
{
	on = false;
}

AboutWindow::~AboutWindow()
{
}

bool AboutWindow::Start()
{
	bool ret = true;

	return ret;
}

void AboutWindow::Draw()
{
	if (ImGui::Begin("About Bull Engine"))
	{
		ImGui::Text("Bull Engine v0.3");
		ImGui::Separator();
		
		ImGui::Text("By Victor Tirado & Sergio Gomez.");
		ImGui::Text("This is a 3D Engine for the subject 3D engines, do it during the 3rd year of\nthe Game Desing and Game Development degree at CITM.");
		ImGui::Separator();

		if (ImGui::CollapsingHeader("Libraries"))
		{
			ImGui::Columns(2, NULL);
			ImGui::Text("Libraries:");
			ImGui::SameLine();
			//ImGui::Separator();
			ImGui::NextColumn();
			ImGui::Text("Version:");
			
			ImGui::Separator();
			ImGui::NextColumn();
			ImGui::Text("Assimp");
			/*ImGui::Separator();
			ImGui::NextColumn();*/
			ImGui::Text("DevIl");
			ImGui::Text("Glew");
			ImGui::Text("ImGui");
			
			ImGui::Text("MathGeoLib");
			ImGui::Text("mmgr");
			ImGui::Text("SDL");
			ImGui::Text("SDL_mixer");
			ImGui::Columns(1, NULL);

		}

		if (ImGui::CollapsingHeader("License"))
		{
			ImGui::Text("MIT License");
			ImGui::Text("\nCopyright (c) 2019 Sersius");
			ImGui::Text("\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the ""Software""), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions : ");
			ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.");
			ImGui::Text("\nTHE SOFTWARE IS PROVIDED ""AS IS"", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
		}
	}
	ImGui::End();
}

bool AboutWindow::CleanUp()
{
	return false;
}