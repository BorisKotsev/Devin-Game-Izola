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

bool checkForMouseCollision(int mouseX, int mouseY, SDL_Rect object)
{
    if (mouseX > object.x && mouseX < object.x + object.w && mouseY > object.y && mouseY < object.y + object.h)
    {
        return true;
    }
    return false;
}

void write(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE)
{
    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color fcolor;
    TTF_Font* font;

    string str = "ttf/Perpetua-Titling-MT.ttf";

    font = TTF_OpenFont(str.c_str(), FONT_SIZE);

    if (font == NULL)
    {
        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    fcolor.r = 0;
    fcolor.g = 0;
    fcolor.b = 0;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t, fcolor);
    texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = coor.x;
    rect.y = coor.y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
