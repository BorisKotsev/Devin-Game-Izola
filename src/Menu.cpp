#include "../headers/Menu.h"
#include "../headers/World.h"

extern World world;

Menu::Menu()
{
    m_menuTexture = nullptr;
}

Menu::~Menu()
{
    //dtor
}

void Menu::init(string configFile)
{
    renderer = world.m_main_renderer;

    configFile = "..\config\\" + configFile;
    fstream stream;

    string tmp;

    string backgroundMap;
    string menuImg;
    string PlayButtonImg;
    string ExitButtonImg;

    stream.open(configFile.c_str());

    stream >> tmp >> menuImg;
    stream >> tmp >> playButton.objectRect.x >> playButton.objectRect.y >> playButton.objectRect.w >> playButton.objectRect.h;
    stream >> tmp >> backgroundMap;
    stream >> tmp >> exitButton.objectRect.x >> exitButton.objectRect.y >> exitButton.objectRect.w >> exitButton.objectRect.h;
    stream >> tmp >> PlayButtonImg;
    stream >> tmp >> ExitButtonImg;
    stream >> tmp >> widthChange >> heightChange;

    stream >> tmp >> playButton.bonusW >> playButton.bonusH;
    stream >> tmp >> exitButton.bonusW;
    stream >> tmp >> exitButton.bonusH;

    stream.close();

    m_menuTexture = LoadTexture(menuImg, renderer);
    m_backgroundMapTexture = LoadTexture(backgroundMap, renderer);
    playButton.objTexture = LoadTexture(PlayButtonImg, renderer);
    exitButton.objTexture = LoadTexture(ExitButtonImg, renderer);

    playButton.startRect = playButton.objectRect;
    exitButton.startRect = exitButton.objectRect;
    playButton.bonusW = 1.6;
    playButton.bonusH = 0.9;

    exitButton.bonusW = 1;
    exitButton.bonusH = 1;
}

void Menu::draw()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, m_menuTexture, NULL, NULL);

    SDL_RenderCopy(renderer, playButton.objTexture, NULL, &(playButton.objectRect));

    SDL_RenderCopy(renderer, exitButton.objTexture, NULL, &(exitButton.objectRect));

    SDL_RenderPresent(renderer);
}

void Menu::buttonHover(Button* button)
{
    if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, button->objectRect))
    {
        if (button->objectRect.w <= button->startRect.w + widthChange)
        {
            button->currentBonusW += button->bonusW;
            button->currentBonusH += button->bonusH;

            button->objectRect.w = button->startRect.w + button->currentBonusW;
            button->objectRect.h = button->startRect.h + button->currentBonusH;
            button->objectRect.x = button->startRect.x - button->currentBonusW / 2;
            button->objectRect.y = button->startRect.y - button->currentBonusH / 2;
        }
    }
    else
    {
        button->currentBonusW = 0;
        button->currentBonusH = 0;

        button->objectRect = button->startRect;
    }
}

void Menu::update()
{
    if (world.m_mouseIsPressed)
    {
        if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, 
                                   playButton.objectRect))
        {
            world.m_quitScene = true;
            world.m_gameState = GAME_STATE::GAME;
        }
        if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y,
                                   exitButton.objectRect))
        {
            world.m_quitScene = true;
            world.m_gameState = GAME_STATE::EXIT;
        }
    }

    buttonHover(&playButton);
    buttonHover(&exitButton);
}