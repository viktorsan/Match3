#include "Game.h"

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char* argv[])
{
	Uint32 frameStart, frameTime;

	if (Game::Instance()->init("ViktorSan's Miner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 755, 600, 0))
	{
		while (Game::Instance()->running())
		{
			frameStart = SDL_GetTicks();

			Game::Instance()->handleEvent();
			Game::Instance()->update();
			Game::Instance()->render();

			frameTime = SDL_GetTicks() - frameStart;
			if(frameTime < DELAY_TIME)
			{
				SDL_Delay((int)(DELAY_TIME - frameTime));
			}
		}
		Game::Instance()->clean();
	} else
	{
		return -1;
	}

	return 0;
}