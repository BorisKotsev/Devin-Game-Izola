#pragma once

#include <vector>
#include "Player.h"
#include "Cell.h"
#include <Common.h>

class Game
{
public:
	Game();
	~Game();

	void draw();
	void update();

	bool offBounds(const coordinates&);
	bool isEmptyCell(const coordinates& coor);

private:
	std::vector<Player*> m_players;
	std::vector<Cell*> cells;
};