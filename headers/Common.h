#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <iostream>
#include <string>
#include <SDL.h>

/*! \class defines
    \brief A header that contains structures and enumerators

    They are used for the different type of game states, ores and more
*/

using namespace std;

#define D(x) cerr << #x << " = " << (x) << " | " << __LINE__ << endl;

enum GAME_STATE
{
    NONE = 0, ///< NONE
    MENU = 1, ///< MENU
    GAME = 2, ///< GAME
    EXIT = 4 ///< EXIT
}; ///< Game state enumerator defining 5 game states to use

enum class CELL_STATE
{
    AVAILABLE = 0,
    PLAYER = 1,
    FORBIDDEN = 2
};

struct UI_object
{
    SDL_Texture* objTexture = NULL;
    SDL_Rect objRect;
};

struct coordinates
{
    int x = 0;
    int y = 0;
};

struct fcoordinates
{
    float x = 0;
    float y = 0;
};

#endif // DEFINES_H_INCLUDED
