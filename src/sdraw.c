#include "main.h"

const int SPEEDS[] =  {658, 478, 378, 298, 228, 178, 138, 108, 88};
static SDL_Surface * screen = NULL;

size S_ARENA =  { S_ARENA_X1,         S_ARENA_Y1 };           /// 20 x 9
size S_SCREEN = { S_ARENA_X1 * 4 + 4, S_ARENA_Y1 * 4 + 13 };  /// 84 x 49

point L_POINTS = {1,                    0 };
point L_TIMER =  { S_ARENA_X1 * 4 - 4,  0 };
point L_BUG =    { S_ARENA_X1 * 4 - 14, 1 };
point L_ARENA =  { 1,                   10 };

void set_arena(size s)
{
    S_ARENA.x = s.x;
    S_ARENA.y = s.y;

    S_SCREEN.x = S_ARENA.x * 4 + 4;  /// 84 x 49
    S_SCREEN.y = S_ARENA.y * 4 + 13;

    L_TIMER.x = S_SCREEN.x - 8;
    L_BUG.x = S_SCREEN.x - 18;
    screen_init();
}

void SDL_SetCaption(const char * caption)
{
    SDL_WM_SetCaption(caption, caption);
}

void screen_init()
{
    if(screen)
        SDL_FreeSurface(screen);

    screen = SDL_SetVideoMode(S_SCREEN.x * S_ZOOM.x, S_SCREEN.y * S_ZOOM.y, 0, SDL_ANYFORMAT);
    DEBUGMALLOC(screen);

    SDL_SetCaption("Snake 2 @ Nokia 3310");
}


color draw_color_background(color front_color)
{
    return front_color == C_PIXEL ? C_BGND : C_PIXEL;
}

static void draw_pixel_xy(int16_t x, int16_t y, color c)
{
    boxColor(screen, x * S_ZOOM.x, y * S_ZOOM.y, (x+1) * S_ZOOM.x - 1, (y+1) * S_ZOOM.y - 1, c);
}

void draw_small_text(const char * text, point p, color c)
{
    while(*text)
    {
        struct nokia_small_char * nchar = nokia_get_small_bold_char(*text);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (7 - j)))
                    draw_pixel_xy(p.x + j, p.y + i, c /* selected ? C_BGND : C_PIXEL */);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_narrow_text(const char * text, point p, color c)
{
    while(*text)
    {
        struct nokia_small_char * nchar = nokia_get_small_char(*text);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (7 - j)))
                    draw_pixel_xy(p.x + j, p.y + i, c);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_big_text(const char * text, point p, color c)
{
    while(*text)
    {
        struct nokia_big_char * nchar = nokia_get_big_char(*text);

        for (int i = 0; i < 15; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (15 - j)))
                    draw_pixel_xy(p.x + j, p.y + i, c);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_pixel(point p, color c)
{
    draw_pixel_xy(p.x, p.y, c);
}

void draw_box(point p, size s, color c)
{
    boxColor(screen, p.x * S_ZOOM.x, p.y * S_ZOOM.y, (p.x+s.x) * S_ZOOM.x - 1, (p.y+s.y) * S_ZOOM.y - 1, c);
}

static void digit(int16_t x, int16_t y, snum n, color c)
{
    for (int j = 0; j < 3; ++j)
        for (int i = 0; i < 5; ++i)
            if (n.col[j] & (1 << (4-i)))
                draw_pixel_xy(x+j, y+i, c);
}

void draw_digits(point p, uint16_t n, uint8_t digits, color c)
{
    draw_box(p, (size){digits * 4, 5}, draw_color_background(c));

    for (int i = 0; i < digits; ++i, n /= 10)
        digit(p.x + 4*(digits-i-1), p.y, numbers[n % 10], c);
}

void draw_clean(point p, color c)
{
    draw_box(arena_to_pixel(p), (size){4, 4}, draw_color_background(c));
}

void draw_item(sitem si, point p, rotation rot, rot_type rt, color c)
{
    draw_bug(si, arena_to_pixel(p), rot, rt, c);
}

void draw_bug(sitem si, point p, rotation rot, rot_type rt, color c)
{
    if (rt == ROTT_NONE)
    {
        for (int i = 0; i < 4; ++i)
                for (int j = 0; j < 8; ++j)
                    if (si.rows[i] & (1 << (7-j)))
                        draw_pixel_xy(p.x+j, p.y+i, c);
        return;
    }
    if (rt == ROTT_CORNERS && rot == ROT_DOWN)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (si.rows[3-j] & (1 << (4+i)))
                    draw_pixel_xy(p.x+j, p.y+i, c);
        return;
    }

    for (int i = 0; i < 4; ++i)
        for (int j = 0; j < 4; ++j)
        {
            int a = i, b = j;
            if (abs(rot) < 2)
            {
                int temp = a;
                a = b;
                b = temp;
            }

            int shifter = (rot > 0) ? 7-b : 4+b;
            if (si.rows[a] & (1 << shifter))
                draw_pixel_xy(p.x+j, p.y+i, c);
        }
}

void draw_points(int n, color c)
{
    if(n >= 0)
        draw_digits(L_POINTS, n, 4, c);
}

void draw_cls(color c)
{
    boxColor(screen, 0, 0, S_SCREEN.x * S_ZOOM.x - 1, S_SCREEN.y * S_ZOOM.y - 1, draw_color_background(c));
}

void draw_init(int points, color c)
{
    draw_cls(c);

    draw_box((point){0, 6}, (size){S_ARENA.x*4+4, 1}, c);

    draw_box((point){0, 9},                (size){S_ARENA.x*4+4, 1}, c);
    draw_box((point){0, 9},                (size){1, S_ARENA.y*4+4}, c);
    draw_box((point){0, S_SCREEN.y - 1},   (size){S_ARENA.x*4+4, 1}, c);
    draw_box((point){S_SCREEN.x - 1, 9},   (size){1, S_ARENA.y*4+4}, c);

    draw_points(points, c);
}

void draw_update(void)
{
    SDL_Flip(screen);
}

void draw_img(const spic * pic, color c)
{
    for (int i = 0; i < S_IMG_Y; ++i)
        for (int j = 0; j < S_IMG_X; ++j)
            if (pic->img[i][j])
                draw_pixel_xy(j + 5, i, c);
}



