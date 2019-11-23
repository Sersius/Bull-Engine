#ifndef _TIMERINGAME_H
#define _TIMERINGAME_H

#include "Globals.h"
#include "SDL/include/SDL.h"

class TimerInGame
{
public:
	TimerInGame();
	~TimerInGame();

	void UpdateTimer();

public:
	bool running;
	bool paused = false;
	float frame_count;
	float time_scale = 1.0f;
	float time;
	float dt;
	float real_dt;
};

#endif // !_TIMERINGAME_H
