#include "../headers/Game.h"

Game::Game()
{

}

Game::~Game()
{
    for (auto& rows : m_cells)
    {
        for (auto& cell : rows)
        {
            delete cell;
        }
    }

    for (auto& player : m_players)
    {
        delete player;
    }
}

void Game::initSession(int size)
{
    m_cells.resize(size);

    for (auto& cell : m_cells)
    {
        cell.resize(size);
    }
}

void Game::load(string configFile)
{
    fstream stream;

    string tmp;
    string whiteCellImg, blackCellImg;

    stream.open(configFile);
    
    stream >> tmp >> m_boardSize;
    stream >> tmp >> whiteCellImg >> blackCellImg;

    stream.close();
}

void Game::draw()
{
    for (auto& rows : m_cells)
    {
        for (auto& cell : rows)
        {
            //cell->draw();
        }
    }
    for (auto& player : m_players)
    {
        player->draw();
    }
}

void Game::update()
{
    for (auto& player : m_players)
    {
        player->update();
    }
}

bool Game::offBounds(const coordinates& coor)
{
    if (coor.x < 0 || coor.y < 0 || coor.x >= m_boardSize || coor.y >= m_boardSize)
    {
        return true;
    }
    return false;
}

bool Game::isEmptyCell(const coordinates& coor)
{
    if (!offBounds(coor))
    {
        if (m_cells[coor.x][coor.y]->getState() == CELL_STATE::AVAILABLE)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    else {
        return false;
    }
}

void Game::placeElimination(const coordinates& coor)
{
    if (!offBounds(coor))
    {
        if (isEmptyCell(coor))
        {
            m_cells[coor.y][coor.x]->setState(CELL_STATE::FORBIDDEN);
        }
    }
}