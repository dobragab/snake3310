#ifndef SMAZE_H_INCLUDED
#define SMAZE_H_INCLUDED

#include "main.h"

void maze_import(const smaze * m);
bool maze_contains(point p);
void maze_delete(void);
void maze_draw(void);
point maze_sp(void);

size maze_multi_size(int num);

#endif // SMAZE_H_INCLUDED
