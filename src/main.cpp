#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

#include "../headers/World.h"

World world;

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
	
	world.init();

	world.m_gameState = MENU;

	while (!world.m_endGame)
	{
		if (world.m_gameState == MENU)
		{
			while (!world.m_quitScene)
			{
				SDL_Delay(25);
			}
			world.m_quitScene = false;
		}
		if (world.m_gameState == GAME)
		{
			world.m_game.initSession(30);
			while (!world.m_quitScene)
			{
				world.input();
				world.m_game.update();
				world.m_game.draw();
				SDL_Delay(25);
			}
			world.m_quitScene = false;
		}
		if (world.m_gameState == EXIT)
		{
			world.destroy();
		}
	}

	return 0; 
}