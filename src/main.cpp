#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

using namespace std;

int main(int argc, char *argv[])
{
	SDL_Init(SDL_INIT_EVERYTHING);
		
	SDL_Window* window;
	window = SDL_CreateWindow("", 100, 100, 500, 500, 0);

	SDL_Renderer* ren = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);

	cout << "test" << endl;

	return 0; 
}