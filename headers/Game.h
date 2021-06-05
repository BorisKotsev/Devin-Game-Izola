#pragma once

#include <vector>
#include "Player.h"
#include "Cell.h"
#include "Common.h"

class Game
{
public:
	Game();
	~Game();

	void load(string configFile);

	void draw();
	void update();

	void initSession(int size);

	bool offBounds(const coordinates&);
	bool isEmptyCell(const coordinates& coor);
	void placeElimination(const coordinates&);

private:
	std::vector<Player*> m_players;
	std::vector <std::vector<Cell*>> m_cells;
	unsigned short m_boardSize;

};