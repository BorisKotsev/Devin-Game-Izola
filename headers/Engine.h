#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#include <string>

using namespace std;

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer);

#endif // ENGINE_H
