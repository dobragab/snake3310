#ifndef SOPT_H_INCLUDED
#define SOPT_H_INCLUDED

#include "main.h"

enum
{
    LEVEL_MIN = 0,
    LEVEL_MAX = 8,

    INTRO_SPEED = 0,
    INTRO_LENGTH = 2,

    FOOD = 1,
    BUG_RATE = 5,
    BUG_TIME = 20,
    SNAKE_LENGTH = 5,
    SNAKE_DIE_LENGTH = 4,

    BUGS_COUNT = 6,
    MAZES_COUNT = 6,

    S_IMG_X = 73,
    S_IMG_Y = 48,

    S_ARENA_X = 20,
    S_ARENA_Y = 9,
//    S_ARENA_X = 8,
//    S_ARENA_Y = 6,
};

extern int LEVEL, MAZE;
extern int S_ZOOM_X, S_ZOOM_Y;

void LoadConfig();
void SaveConfig();

MenuResult TopScore();
MenuResult Level();
MenuResult Zoom();
MenuResult Instructions();

#endif // SOPT_H_INCLUDED
