#ifndef SGAME_H_INCLUDED
#define SGAME_H_INCLUDED

#include "main.h"

MenuResult Continue();
MenuResult SinglePlayer();
MenuResult MultiPlayer();
void FinishGame();
cell cell_contains(point p);

#endif // SGAME_H_INCLUDED
