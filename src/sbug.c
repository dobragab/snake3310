#include "main.h"

static int bug_counter, bug_countdown;
static point bug_pos;
static color c;

void bug_new(color cnew)
{
    bug_counter = 0;
    bug_countdown = 0;
    c = cnew;
}

int bug_count(void)
{
    if (bug_counter != -1)
        bug_counter++;

    return bug_counter;
}

void bug_process(void)
{
    if (bug_counter != -1)
        return;

    if (--(bug_countdown) == 0)
        bug_eat();
    else
        draw_digits(L_TIMER_X, L_TIMER_Y, bug_countdown, 2, c);
}

void bug_generate(color cnew)
{
    bug_counter = -1;
    bug_countdown = BUG_TIME;
    c = cnew;

    point temp;
    do
    {
        temp.x = rand() % (S_ARENA_X - 1);
        temp.y = rand() % S_ARENA_Y;
    } while (cell_contains(temp) != CELL_NONE || cell_contains((point){temp.x+1, temp.y}) != CELL_NONE);

#ifdef DEBUG
    int index = BUGS_COUNT - 1;
#else
    int index = rand() % BUGS_COUNT;
#endif // DEBUG

    draw_item(bugs[index], temp, ROT_RIGHT, ROTT_NONE, c);
    draw_bug(bugs[index], (point){L_BUG_X, L_BUG_Y}, ROT_RIGHT, ROTT_NONE, c);

    draw_digits(L_TIMER_X, L_TIMER_Y, bug_countdown, 2, c);

    bug_pos = temp;
}

int bug_eat(void)
{
    draw_box((point){L_BUG_X, L_BUG_Y}, 8, 4, draw_color_background(c));
    draw_box((point){L_TIMER_X, L_TIMER_Y}, 7, 5, draw_color_background(c));

    point p = bug_pos;
    draw_clean(p, c);
    draw_clean((point){p.x + 1, p.y}, c);

    bug_counter = 0;

    return bug_countdown * 2 + LEVEL * 5 + 5;
}

bool bug_contains(point p)
{
    if (bug_counter != -1)
        return false;

    point b = bug_pos;
    return p.y == b.y && (p.x == b.x || p.x == b.x + 1);
}
