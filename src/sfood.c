#include "main.h"

typedef struct food_s food;

static int num = 0;
static point * data = NULL;
static color c = C_PIXEL;

void food_new(int n, color cnew)
{
    c = cnew;
    data = (point*) malloc (n * sizeof(point));
    debugmalloc(data, "Food-array");

    num = n;

    for(int i = 0; i < n; ++i)
        data[i] = (point){-1, -1};

    int i = 0;
    point temp;
    do
    {
        temp.x = rand() % S_ARENA.x;
        temp.y = rand() % S_ARENA.y;

        if (cell_contains(temp) == CELL_NONE && food_contains(temp) == CELL_NONE)
            data[i++] = temp;

    } while (i < n);
}

void food_delete(void)
{
    free(data);
    data = NULL;
}

void food_draw(void)
{
    for (int i = 0; i < num; ++i)
        draw_item(berry, data[i], ROT_RIGHT, ROTT_NONE, c);
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

point food_eat(point p, color c)
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
        temp.x = rand() % S_ARENA.x;
        temp.y = rand() % S_ARENA.y;
    } while (cell_contains(temp) != CELL_NONE);

    data[i] = temp;

    if (bug_count() == num * BUG_RATE)
    {
        bug_generate(c);
    }

    return temp;
}

