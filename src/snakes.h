#ifndef SNAKES_H_INCLUDED
#define SNAKES_H_INCLUDED

#include "main.h"

typedef snake * snakes;

void snakes_new(int num, int length);
void snakes_delete(void);

bool snakes_alldead(void);
bool snakes_alldying(void);
void snakes_turn(SDLKey key);
void snakes_draw(void);
bool snakes_contains(point p);
void snakes_process();
int snakes_score();

#endif // SNAKES_H_INCLUDED
