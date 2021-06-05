#include "../headers/World.h"
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;

World::World()
{

}

World::~World()
{
    //dtor
}

void World::init()
{
    srand(time(NULL));

    m_SCREEN_WIDTH = 1920;
    m_SCREEN_HEIGHT = 1080;


    SDL_Init(SDL_INIT_EVERYTHING);
    m_main_window = SDL_CreateWindow("Izola", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0);
    m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_PRESENTVSYNC);
    improveRenderer();

    string config = "config\\world.txt";

    string cursorImg;

    ifstream file;

    file.open(config);

    if (file.is_open())
    {
        string tmp;


        file.close();
    }

    m_game.load("game.txt");
    m_menu.init("menu.txt")

    //cursorImg = "img\\menu\\" + cursorImg;

    //SDL_Surface* loadSurface = SDL_LoadBMP((cursorImg.c_str()));
    //SDL_Cursor* cursor = SDL_CreateColorCursor(loadSurface, 10, 5);
    //SDL_SetCursor(cursor);

    //loadSurface = nullptr;
    //cursor = nullptr;
}

void World::input()
{
    m_mouseIsPressed = false;
    m_mouseIsDoubleClicked = false;

    SDL_PollEvent(&m_event);

    if (m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_event.button.clicks >= 2)
        {
            m_mouseIsDoubleClicked = true;
        }

        m_mouseIsPressed = true;
    }

    if (m_event.type == SDL_MOUSEMOTION)
    {
        SDL_GetGlobalMouseState(&(m_mouseCoordinates.x), &(m_mouseCoordinates.y));
        m_mouseCoordinates.x *= m_MOUSE_MULTIPLY_X;
        m_mouseCoordinates.y *= m_MOUSE_MULTIPLY_Y;
    }

}

void World::improveRenderer()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto desktopWidth = DM.w;
    auto desktopHeight = DM.h;

    m_MOUSE_MULTIPLY_X = (double)m_SCREEN_WIDTH / (double)desktopWidth;
    m_MOUSE_MULTIPLY_Y = (double)m_SCREEN_HEIGHT / (double)desktopHeight;

    if (SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    {
        cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << endl;
    }

    SDL_RenderSetLogicalSize(m_main_renderer, 1920, 1080);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void World::destroy()
{
    m_gameState = NONE;
    SDL_DestroyWindow(m_main_window);
    SDL_DestroyRenderer(m_main_renderer);
}
