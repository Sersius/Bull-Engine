#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Globals.h"
#include "SDL/include/SDL.h"
class Window
{
public:
	Window();
	virtual ~Window();

	virtual void Active();
	virtual void Draw() = 0;
	
	
public:
	bool on = true;
};

#endif 