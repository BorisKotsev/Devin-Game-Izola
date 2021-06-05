#include "../headers/Game.h"
#include "../headers/World.h"
#include "../headers/Common.h"

extern World world;

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
    for (unsigned short  y = 0; y < m_boardSize; y ++)
    {
        vector<Cell*> row;
        for (unsigned short x = 0; x < m_boardSize; x++)
        {
            Cell* cell = new Cell();
            row.push_back(cell);
        }
        m_cells.push_back(row);
    }
    D(m_cells.size());
}

void Game::load(string configFile)
{
    fstream stream;

    configFile = "../config/game.txt";

    string tmp;
    string whiteCellImg, blackCellImg, crossImg;

    stream.open(configFile);

    stream >> tmp >> m_boardSize;
    stream >> tmp >> whiteCellImg;
    stream >> tmp >> blackCellImg;
    stream >> tmp >> crossImg;
    stream >> tmp >> m_boardWidth;
    stream >> tmp >> m_topMargin;

    stream.close();

    m_whiteCellTexture = LoadTexture(whiteCellImg, world.m_main_renderer);
    m_blackCellTexture = LoadTexture(blackCellImg, world.m_main_renderer);
    m_crossTexture = LoadTexture(crossImg, world.m_main_renderer);

    m_startOfBoard = (world.m_SCREEN_WIDTH - m_boardWidth) / 2;
    buffRect.w = m_boardWidth / m_boardSize;
    buffRect.h = buffRect.w;
    m_cellWidth = buffRect.w;
}

void Game::draw()
{
    SDL_RenderClear(world.m_main_renderer);
    for (unsigned short y = 0; y < m_cells.size(); y++)
    {
        for (unsigned short x = 0; x < m_cells[y].size(); x++)
        {
            buffRect.x = m_startOfBoard + y * m_cellWidth;
            buffRect.y = m_topMargin + x * m_cellWidth;
            if ((y % 2 == 0 && x % 2 == 0) || (y % 2 == 1 && x % 2 == 1))
            {
                SDL_RenderCopy(world.m_main_renderer, m_whiteCellTexture, NULL, &buffRect);
            }
            else
            {
                SDL_RenderCopy(world.m_main_renderer, m_blackCellTexture, NULL, &buffRect);
            }
            if (m_cells[y][x]->getState() == CELL_STATE::FORBIDDEN)
            {
                SDL_RenderCopy(world.m_main_renderer, m_crossTexture, NULL, &buffRect);
            }
        }
    }
    

    for (auto& player : m_players)
    {
        player->draw();
    }
    
    SDL_RenderPresent(world.m_main_renderer);
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

void Game::addPlayer(string configFile)
{
    if (configFile == "player1.txt")
    {
        Player* player1 = new Player();
        player1->init(configFile);
        m_players.push_back(player1);
    }
    else if (configFile == "player2.txt")
    {
        Player* player2 = new Player();
        player2->init(configFile);
        m_players.push_back(player2);
    }
}