#include "../headers/Menu.h"
#include "../headers/World.h"

extern World world;

Menu::Menu()
{
    m_menuTexture = nullptr;
    isWriting = false;
}

Menu::~Menu()
{
    //dtor
}

void Menu::init(string configFile)
{
    renderer = world.m_main_renderer;

    configFile = "..\\config\\" + configFile;
    fstream stream;

    string tmp;

    string backgroundMap;
    string menuImg;
    string PlayButtonImg;
    string ExitButtonImg;
    string insertImg;
    
    stream.open(configFile.c_str());

    stream >> tmp >> menuImg;
    stream >> tmp >> playButton.objectRect.x >> playButton.objectRect.y >> playButton.objectRect.w >> playButton.objectRect.h;
    stream >> tmp >> exitButton.objectRect.x >> exitButton.objectRect.y >> exitButton.objectRect.w >> exitButton.objectRect.h;
    stream >> tmp >> PlayButtonImg;
    stream >> tmp >> ExitButtonImg;
    stream >> tmp >> widthChange >> heightChange;
    stream >> tmp >> playButton.bonusW >> playButton.bonusH;
    stream >> tmp >> exitButton.bonusW >> exitButton.bonusH;
    stream >> tmp >> m_insertRect.x >> m_insertRect.y >> m_insertRect.w >> m_insertRect.h;
    stream >> tmp >> insertImg;
    stream >> tmp >> m_input;

    stream.close();

    m_menuTexture = LoadTexture(menuImg, renderer);
    playButton.objTexture = LoadTexture(PlayButtonImg, renderer);
    exitButton.objTexture = LoadTexture(ExitButtonImg, renderer);
    m_insertTexture = LoadTexture(insertImg, renderer);

    playButton.startRect = playButton.objectRect;
    exitButton.startRect = exitButton.objectRect;
}

void Menu::draw()
{
    SDL_RenderClear(renderer);

    SDL_RenderCopy(renderer, m_menuTexture, NULL, NULL);

    SDL_RenderCopy(renderer, playButton.objTexture, NULL, &(playButton.objectRect));

    SDL_RenderCopy(renderer, exitButton.objTexture, NULL, &(exitButton.objectRect));

    SDL_RenderCopy(renderer, m_insertTexture, NULL, &(m_insertRect));

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

            if (m_input.size() > 0)
            {
                std::cout << std::stoi(m_input);
                world.m_game.initSession(std::stoi(m_input));
            }
        }
        if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y,
                                   exitButton.objectRect))
        {
            world.m_quitScene = true;
            world.m_gameState = GAME_STATE::EXIT;
        }
        if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y,
            m_insertRect))
        {
            isWriting = true;
            m_input = ""; 
        }
        else
        {
            isWriting = false;
        }
    }

    if (isWriting)
    {
        handleEvent();
    }
    else
    {
        buttonHover(&playButton);
        buttonHover(&exitButton);
    }
}

void Menu::handleEvent()
{
    world.input();
    SDL_Event event = world.m_event;

    if (m_input.size() >= 2)
    {
        return;
    }

    if (event.type == SDL_TEXTINPUT && event.type == SDL_KEYDOWN)
    {
        if (std::isdigit(*event.text.text))
        {
            m_input += event.text.text;
        }
    }

    if (event.key.keysym.sym == SDLK_BACKSPACE && m_input.size() > 0 && event.type != SDL_KEYDOWN)
    {
        m_input = m_input.substr(0, m_input.length() - 1);
    }
}