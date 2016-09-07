#ifndef SMAZE_H_INCLUDED
#define SMAZE_H_INCLUDED

#include "main.h"

void maze_import(const smaze * m);
bool maze_contains(point p);
void maze_delete();
void maze_draw();
point maze_sp();

#endif // SMAZE_H_INCLUDED
