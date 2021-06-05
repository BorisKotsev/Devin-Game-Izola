#include "../headers/Player.h"
#include "../headers/World.h"

extern World world;

Player::Player()
{
    //ctor
}

Player::~Player()
{
    //dtor
}

void Player::init(string configFile)
{
    srand(time(NULL));

    configFile = "..\config\\" + configFile;
    fstream stream;

    string tmp;
    string playerImg;
    string borderImg;

    stream.open(configFile.c_str());

    stream >> tmp >> playerImg;
    stream >> tmp >> borderImg;
    stream >> tmp >> m_speed;

    stream.close();

    m_playerTexture = LoadTexture(playerImg, world.m_main_renderer);
    m_selectedPlayer.objTexture = LoadTexture(borderImg, world.m_main_renderer);

    m_dstRect = m_objRect;
}

void Player::draw()
{
    SDL_Rect screenRect;

    if (world.m_mouseIsDoubleClicked && checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, screenRect))
    {
        m_selectedPlayer.objRect.x = (screenRect.x - 5);
        m_selectedPlayer.objRect.y = (screenRect.y - 5);
        m_selectedPlayer.objRect.w = (screenRect.w + 10);
        m_selectedPlayer.objRect.h = (screenRect.h + 10);

        m_borderActive = true;
    }
    
    SDL_RenderCopy(world.m_main_renderer, m_playerTexture, NULL, &(screenRect));
    
    if (m_borderActive)
    {
        m_selectedPlayer.objRect.x = (screenRect.x - 5);
        m_selectedPlayer.objRect.y = (screenRect.y - 5);
        m_selectedPlayer.objRect.w = (screenRect.w + 10);
        m_selectedPlayer.objRect.h = (screenRect.h + 10);

        SDL_RenderCopy(world.m_main_renderer, m_selectedPlayer.objTexture, NULL, &(m_selectedPlayer.objRect));
    }
}

void Player::update()
{
    SDL_Rect screenRect;

    if (world.m_mouseIsPressed && m_borderActive)
    {
        if (!checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, screenRect))
        {
            m_dstRect.x = world.m_mouseCoordinates.x - m_objRect.w / 2;
            m_dstRect.y = world.m_mouseCoordinates.y - m_objRect.h / 2;

            m_borderActive = false;

            m_moving = true;
        }
    }

    if (m_moving)
    {
        m_direction.x = m_dstRect.x - m_objRect.x;
        m_direction.y = m_dstRect.y - m_objRect.y;

        m_moveRatio = (double)m_direction.x / (double)m_direction.y;

        if (m_direction.x < 0)
        {
            m_coor.x += m_speed * fabs(m_moveRatio) * -1.0;
        }
        else
        {
            m_coor.x += m_speed * fabs(m_moveRatio);
        }

        if (m_direction.y < 0)
        {
            m_coor.y += m_speed * -1.0 / fabs(m_moveRatio);
        }
        else
        {
            m_coor.y += m_speed / fabs(m_moveRatio);
        }

        m_objRect.x = m_coor.x;
        m_objRect.y = m_coor.y;

        if (abs(m_dstRect.x - m_objRect.x) < 5)
        {
            m_moveRatio = false;
        }
    }
}