#include "main.h"

typedef struct top_score
{
    int pos;
    int score;
    color c;

} top_score;

static top_score scores[SNAKES_MAX];
static int count = 0;
static int ticks = 0;

void score_reset(void)
{
    count = 0;
    ticks = 0;
}

void score_tick(void)
{
    ++ticks;
}

void score_add(int score, color c)
{
    scores[count++] = (top_score){ticks, score, c};
}

void score_draw(void)
{
    int last_pos = -1;
    for(int i = count - 1; i >= 0; --i)
    {
        int pos = i;
        if(last_pos >= 0 && scores[i].pos == scores[last_pos].pos)
            pos = last_pos;
        else
            last_pos = i;

        static char buf[BUFSIZ];
        sprintf(buf, "%d %6d", count - pos, scores[i].score);
        draw_small_text(buf, (point){24, (count - i - 1)*8 + 1}, scores[i].c);
    }
}


