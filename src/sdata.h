#ifndef SDATA_H_INCLUDED
#define SDATA_H_INCLUDED

#include "main.h"

typedef enum
{
    CELL_NONE = 0,
    CELL_WALL,
    CELL_FOOD,
    CELL_BUG,
    CELL_SNAKE,

} cell;

typedef struct point
{
    int16_t x, y;
} point;

typedef point size;

typedef enum rotation
{
    ROT_LEFT = -2,
    ROT_UP = -1,
    ROT_DOWN = 1,
    ROT_RIGHT = 2,

} rotation;

typedef enum rot_type
{
    ROTT_NONE,
    ROTT_NORMAL,
    ROTT_CORNERS,

} rot_type;

bool point_equals(point p1, point p2);
rotation corner_rotation (rotation prev, rotation next);
bool rotation_valid (rotation prev, rotation next);
point rot_2_point(rotation rot);
rotation point_diff(point prev, point next);
point arena_next(point p, rotation rot);
point arena_to_pixel(point p);

#endif // SDATA_H_INCLUDED
