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

void Player::init(string configFile, unsigned short width, unsigned short x, unsigned short y)
{
    srand(time(NULL));

    configFile = "..\\config\\" + configFile;
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

    m_logicalCoor.x = x;
    m_logicalCoor.y = y;

    m_objRect.x = world.m_game.logicalToScreen(m_logicalCoor).x;
    m_objRect.y = world.m_game.logicalToScreen(m_logicalCoor).y;
    m_objRect.w = width;
    m_objRect.h = width;

    m_coor.x = m_objRect.x;
    m_coor.y = m_objRect.y;

    m_dstRect = m_objRect;

    m_moving = false;
    m_borderActive = false;

    world.m_mouseIsPressed = false;
}

void Player::draw()
{
    if (world.m_mouseIsDoubleClicked && checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, m_objRect))
    {
        m_selectedPlayer.objRect.x = (m_objRect.x - 5);
        m_selectedPlayer.objRect.y = (m_objRect.y - 5);
        m_selectedPlayer.objRect.w = (m_objRect.w + 10);
        m_selectedPlayer.objRect.h = (m_objRect.h + 10);

        m_borderActive = true;
    }
    
    SDL_RenderCopy(world.m_main_renderer, m_playerTexture, NULL, &(m_objRect));
    
    if (m_borderActive)
    {
        m_selectedPlayer.objRect.x = (m_objRect.x - 5);
        m_selectedPlayer.objRect.y = (m_objRect.y - 5);
        m_selectedPlayer.objRect.w = (m_objRect.w + 10);
        m_selectedPlayer.objRect.h = (m_objRect.h + 10);

        SDL_RenderCopy(world.m_main_renderer, m_selectedPlayer.objTexture, NULL, &(m_selectedPlayer.objRect));
    }
}

void Player::update()
{
    if (world.m_mouseIsPressed && m_borderActive)
    {
        
        if (!checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, m_objRect))
        {
            if (world.m_game.screenCoorToLogical(world.m_mouseCoordinates).x != -1)
            {
                m_dstRect.x = world.m_game.screenCoorToLogical(world.m_mouseCoordinates).x;
                m_dstRect.y = world.m_game.screenCoorToLogical(world.m_mouseCoordinates).y;
                m_logicalCoor.x = m_dstRect.x;
                m_logicalCoor.y = m_dstRect.y;
                coordinates buffCoor;
                buffCoor.x = m_dstRect.x;
                buffCoor.y = m_dstRect.y;
                m_dstRect.x = world.m_game.logicalToScreen(buffCoor).x;
                m_dstRect.y = world.m_game.logicalToScreen(buffCoor).y;

                m_borderActive = false;

                m_moving = true;
            }
        }
        
    }

    if (m_moving)
    {
        m_direction.x = m_dstRect.x - m_objRect.x;
        m_direction.y = m_dstRect.y - m_objRect.y;

        if (m_direction.x > 0)
        {
            m_velocity.x = 1.0f;
        }
        else if (m_direction.x < 0) {
            m_velocity.x = -1.0f;
        }
        else
        {
            m_velocity.x = 0.0f;
        }

        if (m_direction.y > 0)
        {
            m_velocity.y = 1.0f;
        }
        else if (m_direction.y < 0) {
            m_velocity.y = -1.0f;
        }
        else
        {
            m_velocity.y = 0.0f;
        }

        m_coor.x += m_speed * m_velocity.x;
        m_coor.y += m_speed * m_velocity.y;

        m_objRect.x = m_coor.x;
        m_objRect.y = m_coor.y;

        if (abs(m_dstRect.x - m_objRect.x) < 5 && abs(m_dstRect.y - m_objRect.y) < 5)
        {
            m_moving = false;
        }
    }
}