#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "main.h"

typedef struct snake_t snake;

snake * snake_new(point p, int length, rotation dir);
void snake_delete(snake * s);
void snake_draw(const snake * s);
void snake_process(snake * s);
void snake_step(snake * s, bool eat);
void snake_turn(snake * s, rotation r);
cell snake_contains(const snake * s, point p);
void _snake_print(const snake * s);
int snake_score(const snake * s);
bool snake_isdying(const snake * s);
bool snake_isdead(const snake * s);
#ifdef DEBUG
#define snake_print(s) _snake_print(s)
#else
#define snake_print(s)
#endif

#endif // SNAKE_H_INCLUDED
