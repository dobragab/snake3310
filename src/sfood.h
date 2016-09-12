#ifndef SFOOD_H_INCLUDED
#define SFOOD_H_INCLUDED

#include "main.h"

cell food_contains(point p);
point food_eat(point p, color c);
void food_new(int size, color c);
void food_delete(void);
void food_draw(void);

#endif // SFOOD_H_INCLUDED
