#pragma once 

#include <SDL.h>
#include <iostream>
#include <fstream>

#include "Engine.h"
#include "Common.h"

using namespace std;

class Player
{
public:

	Player();
	virtual ~Player();

	void init(string configFile, unsigned short width, unsigned short x, unsigned short y);
	void update();
	void draw();

	SDL_Rect m_objRect;
	SDL_Rect m_dstRect;

	SDL_Texture* m_playerTexture;

    coordinates m_coor;
    coordinates m_direction;
	fcoordinates m_velocity;

    UI_object m_selectedPlayer;

    bool m_borderActive;
	bool m_moving;

    double m_moveRatio;
    double m_speed;

	coordinates m_logicalCoor;
	coordinates m_logicalDstCoor;
};