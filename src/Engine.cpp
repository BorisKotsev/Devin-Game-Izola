#include "../headers/Engine.h"

#include <iostream>

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer)
{
    SDL_Texture* texture = nullptr;

    try
    {
        configFile = "..\\imgs\\" + configFile;

        SDL_Surface* loadingSurface = SDL_LoadBMP(configFile.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        SDL_FreeSurface(loadingSurface);

        if (texture == nullptr)
        {
            throw (-1);
        }

    }
    catch (int i)
    {
        if (i < 0)
        {
            cout << "NO TEXTURE LOADED: " << configFile << endl;
        }
    }
    return texture;
}