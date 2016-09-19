#ifndef SOPT_H_INCLUDED
#define SOPT_H_INCLUDED

#include "main.h"

enum
{
    LEVEL_MIN = 0,
    LEVEL_MAX = 8,

    INTRO_SPEED = 4,
    INTRO_SIZE = 5,
    INTRO_LENGTH = 11,

    FOOD = 1,
    BUG_RATE = 5,
    BUG_TIME = 20,
    SNAKE_LENGTH = 5,
    SNAKE_DIE_LENGTH = 4,
    SNAKES_MAX = 6,

    BUGS_COUNT = 6,
    MAZES_COUNT = 6,

    S_IMG_X = 73,
    S_IMG_Y = 48,

    S_ARENA_X1 = 20,
    S_ARENA_Y1 = 9,
};

extern int LEVEL;
extern int MAZE;
extern int PLAYERS;
extern size S_ZOOM;

void LoadConfig(void);
void SaveConfig(void);

MenuResult TopScore(void);
MenuResult Level(void);
MenuResult Zoom(void);
MenuResult Instructions(void);
MenuResult MultiNum(void);

#endif // SOPT_H_INCLUDED
