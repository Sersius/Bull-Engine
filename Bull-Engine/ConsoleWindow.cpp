#include "Application.h"
#include "ConsoleWindow.h"
#include "Globals.h"
#include "ModuleWindow.h"
#include "imGUI\imgui.h"

ConsoleWindow::ConsoleWindow() : Window()
{
	on = true;
	
}

ConsoleWindow::~ConsoleWindow()
{
}

bool ConsoleWindow::Start()
{
	bool ret = true;

	return ret;
}

void ConsoleWindow::AddLog(const char* fmt, ...) IM_FMTARGS(2)
{
	/*char buf[1024];
	va_list args;
	va_start(args, fmt);
	vsnprintf(buf, _ARRAYSIZE(buf), fmt, args);
	buf[_ARRAYSIZE(buf) - 1] = 0;
	va_end(args);*/
	Items.push_back(Strdup(fmt));
	ScrollToBottom = true;
}

void ConsoleWindow::ClearLog()
{
	for (int i = 0; i < Items.Size; i++)
		free(Items[i]);
	Items.clear();
	ScrollToBottom = true;
}



void ConsoleWindow::Draw()
{
	ImGuiWindowFlags flags = ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
	ImGui::Begin("Console", &on, flags);
	ImGui::SetWindowPos(ImVec2(0, 815), ImGuiCond_Once);
	ImGui::SetWindowSize(ImVec2(App->width,200 ), ImGuiCond_Always);
	SDL_GetWindowSize(App->window->window,&App->width,&App->height);

	
	for (int i = 0; i < Items.Size; i++)
	{
		const char* item = Items[i];
		ImVec4 col = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); 
		if (strstr(item, "[error]")) col = ImColor(1.0f, 0.4f, 0.4f, 1.0f);
		else if (strncmp(item, "# ", 2) == 0) col = ImColor(1.0f, 0.78f, 0.58f, 1.0f);
		ImGui::PushStyleColor(ImGuiCol_Text, col);
		ImGui::TextUnformatted(item);
		ImGui::PopStyleColor();

		
	}
	ImGui::End();

}


