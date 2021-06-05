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
    m_boardSize = size;

    m_startOfBoard = (world.m_SCREEN_WIDTH - m_boardWidth) / 2;
    buffRect.w = m_boardWidth / m_boardSize;
    buffRect.h = buffRect.w;
    m_cellWidth = buffRect.w;

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
    addPlayer("player1.txt");
    addPlayer("player2.txt");
    m_playerOnTurn = 1;
}

void Game::load(string configFile)
{
    fstream stream;

    configFile = "../config/game.txt";

    string tmp;
    string whiteCellImg, blackCellImg, crossImg, player1Turn, player2Turn, player1Wins, player2Wins, selectCellToMove, selectCellToEliminate;

    stream.open(configFile);

    stream >> tmp >> m_boardSize;
    stream >> tmp >> whiteCellImg;
    stream >> tmp >> blackCellImg;
    stream >> tmp >> crossImg;
    stream >> tmp >> m_boardWidth;
    stream >> tmp >> m_topMargin;
    stream >> tmp >> player1Turn;
    stream >> tmp >> player2Turn;
    stream >> tmp >> player1Wins;
    stream >> tmp >> player2Wins;
    stream >> tmp >> selectCellToMove;
    stream >> tmp >> selectCellToEliminate;
    stream >> tmp >> m_screenTextRect.x >> m_screenTextRect.y >> m_screenTextRect.w >> m_screenTextRect.h;
    stream.close();  

    m_whiteCellTexture = LoadTexture(whiteCellImg, world.m_main_renderer);
    m_blackCellTexture = LoadTexture(blackCellImg, world.m_main_renderer);
    m_crossTexture = LoadTexture(crossImg, world.m_main_renderer);

    m_startOfBoard = (world.m_SCREEN_WIDTH - m_boardWidth) / 2;
    buffRect.w = m_boardWidth / m_boardSize;
    buffRect.h = buffRect.w;
    m_cellWidth = buffRect.w;

    m_player1Turn = LoadTexture(player1Turn, world.m_main_renderer);
    m_player2Turn = LoadTexture(player2Turn, world.m_main_renderer);
    m_player1Wins = LoadTexture(player1Wins, world.m_main_renderer);
    m_player2Wins = LoadTexture(player2Wins, world.m_main_renderer);
    m_selectCellToMove = LoadTexture(selectCellToMove, world.m_main_renderer);
    m_selectCellToEliminate = LoadTexture(selectCellToEliminate, world.m_main_renderer);
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

    if (m_playerOnTurn == 1)
    {
        if (m_moved)
        {
            SDL_RenderCopy(world.m_main_renderer, m_selectCellToEliminate, NULL, &(m_screenTextRect));
        }
        else
        {
            SDL_RenderCopy(world.m_main_renderer, m_player1Turn, NULL, &(m_screenTextRect));
        }
    }
    else if (m_playerOnTurn == 2)
    {
        if (m_moved)
        {
            SDL_RenderCopy(world.m_main_renderer, m_selectCellToEliminate, NULL, &(m_screenTextRect));
        }
        else
        {
            SDL_RenderCopy(world.m_main_renderer, m_player2Turn, NULL, &(m_screenTextRect));
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
    if (m_moved)
    {
        if (world.m_mouseIsPressed)
        {
            for (unsigned short y = 0; y < m_cells.size(); y++)
            {
                for (unsigned short x = 0; x < m_cells[y].size(); x++)
                {
                    buffRect.x = m_startOfBoard + y * m_cellWidth;
                    buffRect.y = m_topMargin + x * m_cellWidth;
                    coordinates buff;
                    buff.x = x;
                    buff.y = y;
                    if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, buffRect) && isEmptyCell(buff))
                    {
                        m_cells[y][x]->setState(CELL_STATE::FORBIDDEN);
                        m_moved = false;
                        if (world.m_game.m_playerOnTurn == 1)
                        {
                            world.m_game.m_playerOnTurn = 2;
                        }
                        else
                        {
                            world.m_game.m_playerOnTurn = 1;
                        }
                    }
                }
            }
        }
    }

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
        if (m_cells[coor.y][coor.x]->getState() == CELL_STATE::AVAILABLE)
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
    coordinates coor;
    bool goodPos = false;
    while (!goodPos)
    {
        goodPos = true;
        coor.x = rand() % m_boardSize;
        coor.y = rand() % m_boardSize;
        for (short i = 0; i < m_players.size() && goodPos; i++)
        {
            if (m_players[i]->m_logicalCoor.x == coor.x && m_players[i]->m_logicalCoor.y == coor.y)
            {
                goodPos = false;
            }
        }
    }
    m_cells[coor.y][coor.y]->getState() == CELL_STATE::FORBIDDEN;
    if (configFile == "player1.txt")
    {
        Player* player1 = new Player();
        player1->init(configFile, m_cellWidth, coor.x, coor.y);
        player1->m_index = 1;
        m_players.push_back(player1);
    }
    else if (configFile == "player2.txt")
    {
        Player* player2 = new Player();
        player2->init(configFile, m_cellWidth, coor.x, coor.y);
        player2->m_index = 2;
        m_players.push_back(player2);
    }
}

SDL_Rect Game::syncCoor(coordinates coor)
{
    buffRect.x = m_startOfBoard + coor.y * m_cellWidth;
    buffRect.y = m_topMargin + coor.x * m_cellWidth;
    return buffRect;
}

coordinates Game::screenCoorToLogical(coordinates coor)
{
    for (unsigned short y = 0; y < m_cells.size(); y++)
    {
        for (unsigned short x = 0; x < m_cells[y].size(); x++)
        {
            buffRect.x = m_startOfBoard + y * m_cellWidth;
            buffRect.y = m_topMargin + x * m_cellWidth;
            if (checkForMouseCollision(world.m_mouseCoordinates.x, world.m_mouseCoordinates.y, buffRect))
            {
                coordinates returnValue;
                returnValue.x = x;
                returnValue.y = y;
                return returnValue;
            }
        }
    }
    coordinates returnValue;
    returnValue.x = -1;
    returnValue.y = -1;
}

coordinates Game::logicalToScreen(coordinates coor)
{
    coordinates returnVal;
    returnVal.x = m_startOfBoard + coor.y * m_cellWidth;
    returnVal.y = m_topMargin + coor.x * m_cellWidth;
    return returnVal;
}

bool Game::checkForMove(coordinates start, coordinates end, int index)
{
    if (index == m_playerOnTurn)
    {
        if (abs(start.x - end.x) >= 2 || abs(start.y - end.y) >= 2 || m_cells[end.y][end.x]->getState() == CELL_STATE::FORBIDDEN || m_cells[end.y][end.x]->getState() == CELL_STATE::TAKEN || m_moved)
        {
            return false;
        }
    }
    else
    {
        return false;
    }
    
    return true;
}