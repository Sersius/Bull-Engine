#include "Window.h"

Window::Window()
{}

Window::~Window()
{}

void Window::Active()
{
	on = !on;
}


bool Window::IsActivated()
{
	return on;
}

