#ifndef SNAKES_H_INCLUDED
#define SNAKES_H_INCLUDED

#include "main.h"

void snakes_new(int num, int length);
void snakes_delete(void);

bool snakes_alldead(void);
bool snakes_alldying(void);
void snakes_turn(SDLKey key);
void snakes_draw(void);
bool snakes_contains(point p);
bool snakes_canstep(const snake * s, point p);
void snakes_process(void);
int snakes_score(void);
void snakes_add_score(void);

#endif // SNAKES_H_INCLUDED
