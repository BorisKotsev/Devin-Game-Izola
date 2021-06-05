#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include "SDL.h"

#include "Common.h"

using namespace std;

class Menu
{
public:
    Menu();
    virtual ~Menu();
    SDL_Renderer* renderer;

    Button playButton;
    Button exitButton;

    SDL_Texture* m_menuTexture;
    SDL_Texture* m_backgroundMapTexture;
    SDL_Texture* m_insertTexture;

    SDL_Rect m_insertRect;

    int widthChange, heightChange;

    void init(string configFile);
    void draw();
    void update();
    void buttonHover(Button* button);

    void handleEvent();
private:
    std::string m_input;
    bool isWriting;
};