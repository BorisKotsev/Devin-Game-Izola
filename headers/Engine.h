#ifndef ENGINE_H
#define ENGINE_H

#include <SDL.h>

#include <string>

using namespace std;

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer);
bool checkForMouseCollision(int mouseX, int mouseY, SDL_Rect object);

#endif // ENGINE_H
