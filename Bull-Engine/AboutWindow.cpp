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
	ImGui::Begin("About Bull Engine", &on, 0);
	
		ImGui::Text("Bull Engine v0.3");
		ImGui::Separator();
		
		ImGui::Text("By Victor Tirado & Sergio Gomez.");
		ImGui::Text("This is a 3D Engine for the subject 3D engines, do it during the 3rd year of\nthe Game Desing and Game Development degree at CITM.");
		ImGui::Separator();	

		if (ImGui::Button("Github repository"))
			ShellExecute(GetActiveWindow(), "open", "https://github.com/Sersius/Bull-Engine", NULL, NULL, SW_SHOWNORMAL);
		ImGui::SameLine();
		if (ImGui::Button("Download last release"))
			ShellExecute(GetActiveWindow(), "open", "https://github.com/Sersius/Bull-Engine/releases", NULL, NULL, SW_SHOWNORMAL);
		ImGui::SameLine();
		if (ImGui::Button("Report a issue"))
			ShellExecute(GetActiveWindow(), "open", "https://github.com/Sersius/Bull-Engine/issues", NULL, NULL, SW_SHOWNORMAL);

		if (ImGui::CollapsingHeader("Libraries"))
		{
			ImGui::Columns(2, NULL);
			ImGui::Text("Libraries:");
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("Version:");
			
			ImGui::Separator();

			ImGui::NextColumn();
			ImGui::MenuItem("SDL");
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v4.0.2");

			ImGui::NextColumn();
			if (ImGui::MenuItem("DevIl"))
				ShellExecute(GetActiveWindow(), "open", "http://openil.sourceforge.net/download.php", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v1.8.0");

			ImGui::NextColumn();
			if (ImGui::MenuItem("OpenGL"))
				ShellExecute(GetActiveWindow(), "open", "https://opengl.es.jaleco.com", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v4.6");

			ImGui::NextColumn();
			if (ImGui::MenuItem("Glew"))
				ShellExecute(GetActiveWindow(), "open", "http://glew.sourceforge.net/", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v2.1.0");

			ImGui::NextColumn();
			if (ImGui::MenuItem("ImGui"))
				ShellExecute(GetActiveWindow(), "open", "https://github.com/ocornut/imgui/releases/tag/v1.72", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v1.72");
			
			ImGui::NextColumn();
			if (ImGui::MenuItem("MathGeoLib"))
				ShellExecute(GetActiveWindow(), "open", "https://github.com/juj/MathGeoLib/releases/tag/v1.5", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("v1.5");

			ImGui::NextColumn();
			if (ImGui::MenuItem("Assimp"))
				ShellExecute(GetActiveWindow(), "open", "http://www.assimp.org/index.php/downloads", NULL, NULL, SW_SHOWNORMAL);
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("");

			ImGui::NextColumn();
			ImGui::Text("mmgr");
			ImGui::SameLine();
			ImGui::NextColumn();
			ImGui::Text("");

			ImGui::Columns(1, NULL);

		}

		if (ImGui::CollapsingHeader("License"))
		{
			ImGui::Text("MIT License");
			ImGui::Text("\nCopyright (c) 2019 Victor Tirado & Sergio Gomez");
			ImGui::Text("\nPermission is hereby granted, free of charge, to any person obtaining a copy\nof this software and associated documentation files(the ""Software""), to deal\nin the Software without restriction, including without limitation the rights\nto use, copy, modify, merge, publish, distribute, sublicense, and/or sell\ncopies of the Software, and to permit persons to whom the Software is\nfurnished to do so, subject to the following conditions : ");
			ImGui::Text("\nThe above copyright notice and this permission notice shall be included in all\ncopies or substantial portions of the Software.");
			ImGui::Text("\nTHE SOFTWARE IS PROVIDED ""AS IS"", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR\nIMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,\nFITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE\nAUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER\nLIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,\nOUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE\nSOFTWARE.");
		}
	
	ImGui::End();
}

bool AboutWindow::CleanUp()
{
	return false;
}