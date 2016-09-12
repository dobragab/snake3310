#include "main.h"

typedef struct snode_t /// snode
{
    point pos;
    bool food;
    struct snode_t *next, *prev;

} snode;

struct snake_t /// snake
{
    rotation rot_cur, rot_next;
    int16_t die, length, score;
    bool moved;
    snake_profile profile;
    point nextpos;

    snode *head, *tail;
};

snake * snake_new(point p, int length, rotation dir, snake_profile profile)
{
    point diff = rot_2_point(dir);

    snake * result = (snake*) malloc(sizeof(snake));
    debugmalloc(result, "Snake");

    result->head = (snode*) malloc(sizeof(snode));
    debugmalloc(result->head, "Snake-head");

    result->rot_cur = -dir;
    result->rot_next = -dir;
    result->die = -1;
    result->length = 0;
    result->score = 0;
    result->moved = false;
    result->profile = profile;

    snode * iter = result->head;

    iter->prev = NULL;
    iter->food = false;
    iter->pos = p;
    p.x += diff.x,
    p.y += diff.y;

    for (int i = 0; i < length+1; ++i)
    {
        iter->next = (snode*) malloc(sizeof(snode));
        debugmalloc(iter->next, "Snake-node");

        iter->next->prev = iter;

        iter = iter->next;

        iter->pos = p;
        iter->food = false;
        p.x += diff.x,
        p.y += diff.y;
    }

    result->tail = iter;
    iter->next = NULL;

    return result;
}

int snake_score(const snake * s)
{
    return s->score;
}

void _snake_print(const snake * s)
{
    if (!s)
        return;

    for (snode * iter = s->head; iter != NULL; iter = iter->next)
    {
        printf(iter->food ? "%d %d x\n" : "%d %d\n", iter->pos.x, iter->pos.y);
    }
    putchar('\n');}

static void snake_clean(const snake * s)
{
    if (!s || !(s->head))
        return;

    if(s->profile.c == C_PIXEL || s->die == 0)
        for(snode * iter = s->head; iter != NULL; iter = iter->next)
            draw_clean(iter->pos, s->profile.c);
    else
        snake_draw_color(s, C_WHITE);
}

void snake_draw(const snake * s)
{
    snake_draw_color(s, s->profile.c);
}

void snake_draw_color(const snake * s, color c)
{
    if (!s || !(s->head))
        return;

    rotation cur = point_diff(s->head->pos, s->head->next->pos);
    draw_item(parts[PART_HEAD], s->head->pos, cur, ROTT_NORMAL, c);

    for (snode *iter = s->head->next; iter->next != NULL; iter = iter->next)
    {
        rotation next = point_diff(iter->pos, iter->next->pos);

        if (cur == next)
            draw_item (parts[PART_BODY + iter->food], iter->pos, cur, ROTT_NORMAL, c);
        else
            draw_item (parts[PART_CORNER + iter->food], iter->pos, corner_rotation (next, cur), ROTT_CORNERS, c);

        cur = next;
    }

    rotation diff = point_diff(s->tail->prev->pos, s->tail->pos);

    draw_item(parts[PART_TAIL], s->tail->pos, diff, ROTT_NORMAL, c);
}

bool snake_turn(snake * s, SDLKey key)
{
    for(int i = 0; i < 5; ++i)
        if(s->profile.keys[i] == key)
        {
            rotation r = i - 2;
            if (rotation_valid(s->rot_cur, r))
                s->rot_next = r;
            return true;
        }
    return false;
}

static void snake_free_tail(snake * s)
{
    snode * iter = s->head, *temp;
    while (iter != NULL)
    {
        temp = iter->next;
        free(iter);
        iter = temp;
    }
}

void snake_delete(snake * s)
{
    snake_free_tail(s);
    free(s);
}

static void snake_kill(snake * s)
{
    if (!s)
        return;

    snake_free_tail(s);
    s->head = NULL;
}

bool snake_isdead(const snake * s)
{
    return !(s && s->head);
}

bool snake_isdying(const snake * s)
{
    return !s || s->die != -1;
}

static void snake_prepend(snake * s)
{
    point oldpos = s->head->pos;

    snode * temp = s->head;
    s->head = (snode *) malloc(sizeof(snode));
    debugmalloc(s->head, "Snake-step");

    s->head->next = temp;
    s->head->prev = NULL;
    s->head->next->prev = s->head;

    s->head->pos = arena_next(oldpos, s->rot_next);
}

static void snake_pop_tail(snake * s)
{
    snode * temp = s->tail;
    s->tail = s->tail->prev;
    s->tail->next = NULL;
    free(temp);
}

cell snake_contains(const snake * s, point p)
{
    if (s->moved)
    {
        for (snode * iter = s->head; iter->next != NULL; iter = iter->next)
            if (point_equals(iter->pos, p))
                return CELL_SNAKE;
    }
    else
    {
        for (snode * iter = s->head; iter != NULL; iter = iter->next)
            if (point_equals(iter->pos, p))
                return CELL_SNAKE;
    }

    return CELL_NONE;
}

point snake_get_next(const snake * s)
{
    return s->nextpos;
}

void snake_next(snake * s)
{
    if (s == NULL)
        return;

    if (s->die < 0)
        s->nextpos = arena_next(s->head->pos, s->rot_next);
}

void snake_process(snake * s)
{
    if (s == NULL)
        return;

    if (s->die == 0)
    {
        snake_kill(s);
        return;
    }
    else if (s->die > 0)
    {
        if (--(s->die) % 2)
            snake_draw(s);
        else
            snake_clean(s);

        return;
    }

    s->moved = true;
    cell nextcell = cell_contains(s->nextpos);
    s->moved = false;

    if (nextcell == CELL_FOOD)
    {
        s->length += 1;
        s->score += LEVEL;

        point nextfood = food_eat(s->nextpos, s->profile.c);

        snake_step(s, true);

        draw_item(berry, nextfood, ROT_RIGHT, ROTT_NONE, s->profile.c);
    }
    else if (nextcell == CELL_BUG)
    {
        s->length += 1;
        s->score += bug_eat();

        snake_step(s, true);
    }
    else if (nextcell == CELL_SNAKE || nextcell == CELL_WALL || !snakes_canstep(s, s->nextpos))
    {
        s->die = 2*SNAKE_DIE_LENGTH;
        snake_clean(s);
    }
    else
    {
        snake_step(s, false);
    }
}

void snake_step(snake * s, bool eat)
{
    if (!s || !(s->head))
        return;

    s->moved = false;

    if (!eat)
    {
        draw_clean(s->tail->pos, s->profile.c);
        draw_clean(s->tail->prev->pos, s->profile.c);
        snake_pop_tail(s);

        rotation diff = point_diff(s->tail->prev->pos, s->tail->pos);

        draw_item(parts[PART_TAIL], s->tail->pos, diff, ROTT_NORMAL, s->profile.c);
    }

    draw_clean(s->head->pos, s->profile.c);
    if (s->rot_cur == s->rot_next)
        draw_item(parts[PART_BODY + s->head->food], s->head->pos, s->rot_cur, ROTT_NORMAL, s->profile.c);
    else
        draw_item(parts[PART_CORNER + s->head->food], s->head->pos, corner_rotation(s->rot_cur, s->rot_next), ROTT_CORNERS, s->profile.c);

    snake_prepend(s);
    s->head->food = eat;
    s->rot_cur = s->rot_next;

    if (eat)
        draw_clean(s->head->pos, s->profile.c);

    cell nextcell = cell_contains(arena_next(s->head->pos, s->rot_cur));
    bool nexteat = nextcell == CELL_FOOD || nextcell == CELL_BUG;

    draw_item(parts[PART_HEAD + nexteat], s->head->pos, s->rot_cur, ROTT_NORMAL, s->profile.c);
}

