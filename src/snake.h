#ifndef SNAKE_H_INCLUDED
#define SNAKE_H_INCLUDED

#include "main.h"

typedef struct snake_t snake;

typedef struct
{
    color c;
    SDLKey keys[5]; // in { LEFT, UP, unused, DOWN, RIGHT } order

} snake_profile;

snake * snake_new(point p, int length, rotation dir, snake_profile profile);
void snake_delete(snake * s);
void snake_draw(const snake * s);
void snake_draw_color(const snake * s, color c);
void snake_next(snake * s);
void snake_process(snake * s);
void snake_step(snake * s, bool eat);
bool snake_turn(snake * s, SDLKey key);
cell snake_contains(const snake * s, point p);
point snake_get_next(const snake * s);
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
