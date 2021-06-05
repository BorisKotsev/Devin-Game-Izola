#pragma once

#include <vector>
#include "Player.h"
#include "Cell.h"

class Game
{
public:
	Game();
	~Game();

private:
	std::vector<Player*> m_players;
	std::vector<Cell*> cells;
};