#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <vector>
#include <fstream>

#include <SDL.h>

#include "Game.h"
#include "Common.h"

class World
{
public:
    World();
    virtual ~World();

    SDL_Renderer* m_main_renderer;
    SDL_Window* m_main_window;

    int m_SCREEN_WIDTH;
    int m_SCREEN_HEIGHT;
    double m_MOUSE_MULTIPLY_X;
    double m_MOUSE_MULTIPLY_Y;

    bool m_mouseIsPressed;
    bool m_mouseIsDoubleClicked;
    bool m_quitScene;
    bool m_endGame;

    SDL_Event m_event;

    GAME_STATE m_gameState;

    coordinates m_mouseCoordinates;

    Game m_game;

    void init();
    void input();
    void improveRenderer();
    void destroy();

protected:

private:
};

#endif