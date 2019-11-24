#include "TimerInGame.h"
#include "Application.h"

TimerInGame::TimerInGame()
{
	
}

TimerInGame::~TimerInGame()
{

}

void TimerInGame::UpdateTimer()
{
	frame_count++;
	real_dt = App->GetDT();
	//realTimeSinceStartup += realTimeDeltaTime;

	if (App->scene_intro->game_running == false) {
		time = 0.0f;
	}
	else if (App->scene_intro->game_running == true &&App->scene_intro->timer_in_game.paused == false) {
		time += real_dt * time_scale;
		dt = real_dt * time_scale;
	}

	if (App->scene_intro->timer_in_game.paused == true)
	{
		time = time;
	}
}