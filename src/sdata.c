#include "main.h"

bool point_equals(point p1, point p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

rotation corner_rotation (rotation prev, rotation next)
{
    if (abs(prev) > 1)
    {
        int temp = -next;
        next = -prev;
        prev = temp;
    }
    int result = (prev < 0) + 1;
    return prev*next > 0 ? -result : result;
}

bool rotation_valid (rotation prev, rotation next)
{
    return prev != -next;
}

point rot_2_point(rotation rot)
{
    return (point){rot / 2, rot % 2};
}

rotation point_diff(point prev, point next)
{
    int result = (2 * (prev.x - next.x) + prev.y - next.y);

    if (result == 2*S_ARENA.x - 2)
        return ROT_LEFT;
    if (result == 2 - 2*S_ARENA.x)
        return ROT_RIGHT;

    if (result == S_ARENA.y - 1)
        return ROT_UP;
    if (result == 1 - S_ARENA.y)
        return ROT_DOWN;

    return result;
}

point arena_next(point p, rotation rot)
{
    point diff = rot_2_point(rot);
    point temp = (point){.x = p.x + diff.x, .y = p.y + diff.y};

    if (temp.x < 0)
        temp.x = S_ARENA.x - 1;
    else if (temp.x >= S_ARENA.x)
        temp.x = 0;

    if (temp.y < 0)
        temp.y = S_ARENA.y - 1;
    else if (temp.y >= S_ARENA.y)
        temp.y = 0;

    return temp;
}

point arena_to_pixel(point p)
{
    return (point) {.x = p.x * 4 + L_ARENA.x + 1, .y = p.y * 4 + L_ARENA.y + 1};
}

