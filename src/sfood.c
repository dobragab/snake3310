#include "main.h"

typedef struct food_s food;

static int num = 0;
static point * data = NULL;

void food_new(int n)
{
    data = (point*) malloc (n * sizeof(point));
    debugmalloc(data, "Food-array");

    num = n;

    for(int i = 0; i < n; ++i)
        data[i] = (point){-1, -1};

    int i = 0;
    point temp;
    do
    {
        temp.x = rand() % S_ARENA_X;
        temp.y = rand() % S_ARENA_Y;

        if (cell_contains(temp) == CELL_NONE && food_contains(temp) == CELL_NONE)
            data[i++] = temp;

    } while (i < n);
}

void food_delete()
{
    free(data);
    data = NULL;
}

void food_draw()
{
    for (int i = 0; i < num; ++i)
        draw_item(berry, data[i], ROT_RIGHT, ROTT_NONE);
}

cell food_contains(point p)
{
    if (!data)
        return CELL_NONE;

    for (int i = 0; i < num; ++i)
        if (point_equals(p, data[i]))
            return CELL_FOOD;

    return CELL_NONE;
}

point food_eat(point p)
{
    if (!data || num == 0)
        return p;

    int i = 0;
    while (!point_equals(data[i], p) && i < num)
        ++i;

    if (i == num)
        return p;

    point temp;
    do
    {
        temp.x = rand() % S_ARENA_X;
        temp.y = rand() % S_ARENA_Y;
    } while (cell_contains(temp) != CELL_NONE);

    data[i] = temp;

    if (bug_count() == num * BUG_RATE)
    {
        bug_generate();
    }

    return temp;
}

