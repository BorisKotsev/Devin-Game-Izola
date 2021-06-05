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

	SDL_Texture* m_playerTexture;
	SDL_Texture* m_borderTexture;

};