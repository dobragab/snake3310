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

    snode *head, *tail;
};

snake * snake_new(point p, int length, rotation dir)
{
    point diff = rot_2_point(dir);

    snake * result = (snake*) malloc(sizeof(snake));
    debugmalloc(result, "Snake");

    result->head = (snode*) malloc(sizeof(snode));
    debugmalloc(result->head, "Snake-head");

    result->rot_cur = ROT_RIGHT;
    result->rot_next = ROT_RIGHT;
    result->length = 0;
    result->score = 0;
    result->die = -1;
    result->moved = false;

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

        iter->food = false;
        iter->pos = p;
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

    for(snode * iter = s->head; iter != NULL; iter = iter->next)
        draw_clean(iter->pos);
}

void snake_draw(const snake * s)
{
    if (!s || !(s->head))
        return;

    rotation cur = point_diff(s->head->pos, s->head->next->pos);
    draw_item(parts[PART_HEAD], s->head->pos, cur, ROTT_NORMAL);

    for (snode *iter = s->head->next; iter->next != NULL; iter = iter->next)
    {
        rotation next = point_diff(iter->pos, iter->next->pos);

        if (cur == next)
            draw_item (parts[PART_BODY + iter->food], iter->pos, cur, ROTT_NORMAL);
        else
            draw_item (parts[PART_CORNER + iter->food], iter->pos, corner_rotation (next, cur), ROTT_CORNERS);

        cur = next;
    }

    rotation diff = point_diff(s->tail->prev->pos, s->tail->pos);

    draw_item(parts[PART_TAIL], s->tail->pos, diff, ROTT_NORMAL);
}

void snake_turn(snake * s, rotation r)
{
    if (rotation_valid(s->rot_cur, r))
        s->rot_next = r;
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

void snake_process(snake * s)
{
    point nextpos = arena_next(s->head->pos, s->rot_next);

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
    cell nextcell = cell_contains(nextpos);
    s->moved = false;

    if (nextcell == CELL_FOOD)
    {
        s->length += 1;
        s->score += LEVEL + 1;

        point nextfood = food_eat(nextpos);

        snake_step(s, true);

        draw_item(berry, nextfood, ROT_RIGHT, ROTT_NONE);
    }
    else if (nextcell == CELL_BUG)
    {
        s->length += 1;
        s->score += bug_eat();

        snake_step(s, true);
    }
    else if (nextcell == CELL_SNAKE || nextcell == CELL_WALL)
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
        draw_clean(s->tail->pos);
        draw_clean(s->tail->prev->pos);
        snake_pop_tail(s);

        rotation diff = point_diff(s->tail->prev->pos, s->tail->pos);

        draw_item(parts[PART_TAIL], s->tail->pos, diff, ROTT_NORMAL);
    }

    draw_clean(s->head->pos);
    if (s->rot_cur == s->rot_next)
        draw_item(parts[PART_BODY + s->head->food], s->head->pos, s->rot_cur, ROTT_NORMAL);
    else
        draw_item(parts[PART_CORNER + s->head->food], s->head->pos, corner_rotation(s->rot_cur, s->rot_next), ROTT_CORNERS);

    snake_prepend(s);
    s->head->food = eat;
    s->rot_cur = s->rot_next;

    if (eat)
        draw_clean(s->head->pos);

    cell nextcell = cell_contains(arena_next(s->head->pos, s->rot_cur));
    bool nexteat = nextcell == CELL_FOOD || nextcell == CELL_BUG;

    draw_item(parts[PART_HEAD + nexteat], s->head->pos, s->rot_cur, ROTT_NORMAL);

}

