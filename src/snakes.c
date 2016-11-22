#include "main.h"

typedef snake * snakes;

static snake_profile profile_single =
{ .keys = { SDLK_LEFT, SDLK_UP, 0, SDLK_DOWN, SDLK_RIGHT }, .c = C_PIXEL };

static snake_profile profiles[] =
{
    { .keys = { SDLK_LEFT,      SDLK_UP,            0, SDLK_DOWN,   SDLK_RIGHT      }, .c = 0xFF0000FF }, // Fred
    { .keys = { SDLK_a,         SDLK_w,             0, SDLK_s,      SDLK_d          }, .c = 0x00FF00FF }, // Greenlee
    { .keys = { SDLK_f,         SDLK_t,             0, SDLK_g,      SDLK_h          }, .c = 0xFF00FFFF }, // Pinkney
    { .keys = { SDLK_j,         SDLK_i,             0, SDLK_k,      SDLK_l          }, .c = 0x00FFFFFF }, // Bluebell
    { .keys = { SDLK_SEMICOLON, SDLK_LEFTBRACKET,   0, SDLK_QUOTE,  SDLK_BACKSLASH  }, .c = 0xFF8000FF }, // Willem
    { .keys = { SDLK_KP4,       SDLK_KP8,           0, SDLK_KP5,    SDLK_KP6        }, .c = 0xCCCCCCFF }, // Greydon
};

static snakes * snakes_instance = NULL;

void snakes_new(int num, int length)
{
    snakes_instance = (snakes*) malloc((num + 1) * sizeof(snakes));
    if(num == 1)
    {
        snakes_instance[0] = snake_new(maze_sp(), length, ROT_LEFT, profile_single);
    }
    else
    {
        size mazesize = maze_multi_size(num);
        int half = SNAKES_MAX / 2;
        int gapnum = num < half ? num : half;
        double gap = (double)(mazesize.y - gapnum + 1) / (double)(gapnum);

        for(int i = 0; i < num; ++i)
        {
            int y = gap/2 + (gap + 1)*(i % half);
            point sp = { .x = (i < half ? 8 : mazesize.x - 8), .y = y };
            snakes_instance[i] = snake_new(sp, length, (i < half ? ROT_LEFT : ROT_RIGHT), profiles[i]);
        }
    }
    snakes_instance[num] = NULL;
}

void snakes_delete(void)
{
    if(snakes_instance == NULL)
        return;

    for(int i = 0; snakes_instance[i] != NULL; ++i)
        snake_delete(snakes_instance[i]);

    free(snakes_instance);
}

bool snakes_alldead(void)
{
    int alive = 0;
    int i;
    for(i = 0; snakes_instance[i] != NULL; ++i)
        if(!snake_isdead(snakes_instance[i]))
           alive++;

    return i == 1 ? alive == 0 : alive <= 1;
}

bool snakes_alldying(void)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        if(!snake_isdying(snakes_instance[i]))
           return false;

    return true;
}

void snakes_turn(SDLKey key)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        if(snake_turn(snakes_instance[i], key))
           return;
}

void snakes_draw(void)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        snake_draw(snakes_instance[i]);
}

bool snakes_contains(point p)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        if(snake_contains(snakes_instance[i], p))
           return true;

    return false;
}

bool snakes_canstep(const snake * s, point p)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        if(s != snakes_instance[i] &&
           !snake_isdying(s) &&
           point_equals(snake_get_next(snakes_instance[i]), p))
           return false;

    return true;
}

int snakes_score(void)
{
    if(snakes_instance[0] != NULL && snakes_instance[1] == NULL)
        return snake_score(snakes_instance[0]);
    return -1;
}

void snakes_process(void)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        snake_next(snakes_instance[i]);

    for(int i = 0; snakes_instance[i] != NULL; ++i)
        snake_process(snakes_instance[i]);
}

void snakes_add_score(void)
{
    for(int i = 0; snakes_instance[i] != NULL; ++i)
        if(!snake_isdying(snakes_instance[i]))
           snake_add_score(snakes_instance[i]);
}

