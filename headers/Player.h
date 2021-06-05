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

	void init(string configFile);
	void update();
	void draw();

	SDL_Rect m_objRect;
	SDL_Rect m_dstRect;

	SDL_Texture* m_playerTexture;

    coordinates m_coor;
    coordinates m_direction;

    UI_object m_selectedPlayer;

    bool m_borderActive;
	bool m_moving;

    double m_moveRatio;
    double m_speed;
};