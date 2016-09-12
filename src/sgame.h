#ifndef SGAME_H_INCLUDED
#define SGAME_H_INCLUDED

#include "main.h"

MenuResult Continue(void);
MenuResult SinglePlayer(void);
MenuResult MultiPlayer(void);
void FinishGame(void);
cell cell_contains(point p);

#endif // SGAME_H_INCLUDED
