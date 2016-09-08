#include "main.h"

const int SPEEDS[] =  {658, 478, 378, 298, 228, 178, 138, 108, 88};
static SDL_Surface * screen = NULL;

int S_SCREEN_X = S_ARENA_X1 * 4 + 4;  /// 84 x 49
int S_SCREEN_Y = S_ARENA_Y1 * 4 + 13;

int L_POINTS_X = 1;
int L_POINTS_Y = 0;

int L_TIMER_X = S_ARENA_X1 * 4 + 4 - 8;
int L_TIMER_Y = 0;

int L_BUG_X = S_ARENA_X1 * 4 + 4 - 18;
int L_BUG_Y = 1;

int L_ARENA_X = 1;
int L_ARENA_Y = 10;

void set_arena(size s)
{
    S_ARENA_X = s.x;
    S_ARENA_Y = s.y;

    S_SCREEN_X = S_ARENA_X * 4 + 4;  /// 84 x 49
    S_SCREEN_Y = S_ARENA_Y * 4 + 13;

    L_TIMER_X = S_SCREEN_X - 8;
    L_BUG_X = S_SCREEN_X - 18;
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

    screen = SDL_SetVideoMode(S_SCREEN_X * S_ZOOM_X, S_SCREEN_Y * S_ZOOM_Y, 0, SDL_ANYFORMAT);
    DEBUGMALLOC(screen);

    SDL_SetCaption("Snake 2 @ Nokia 3310");
}


color draw_color_background(color front_color)
{
    return front_color == C_PIXEL ? C_BGND : C_PIXEL;
}

void draw_small_text(const char * text, point p, bool selected)
{
    while(*text)
    {
        struct nokia_small_char * nchar = nokia_get_small_bold_char(*text);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (7 - j)))
                    draw_pixel(p.x + j, p.y + i, selected ? C_BGND : C_PIXEL);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_narrow_text(const char * text, point p, bool selected)
{
    while(*text)
    {
        struct nokia_small_char * nchar = nokia_get_small_char(*text);

        for (int i = 0; i < 8; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (7 - j)))
                    draw_pixel(p.x + j, p.y + i, selected ? C_BGND : C_PIXEL);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_big_text(const char * text, point p, bool selected)
{
    while(*text)
    {
        struct nokia_big_char * nchar = nokia_get_big_char(*text);

        for (int i = 0; i < 15; ++i)
            for (int j = 0; j < nchar->width; ++j)
                if (nchar->rows[i] & (1 << (15 - j)))
                    draw_pixel(p.x + j, p.y + i, selected ? C_BGND : C_PIXEL);

        p.x += nchar->advance;

        ++text;
    }
}

void draw_pixel(int16_t x, int16_t y, color c)
{
    boxColor(screen, x * S_ZOOM_X, y * S_ZOOM_Y, (x+1) * S_ZOOM_X - 1, (y+1) * S_ZOOM_Y - 1, c);
}

void draw_box(point p, int16_t w, int16_t h, color c)
{
    boxColor(screen, p.x * S_ZOOM_X, p.y * S_ZOOM_Y, (p.x+w) * S_ZOOM_X - 1, (p.y+h) * S_ZOOM_Y - 1, c);
}

static void digit(int16_t x, int16_t y, snum n, color c)
{
    for (int j = 0; j < 3; ++j)
        for (int i = 0; i < 5; ++i)
            if (n.col[j] & (1 << (4-i)))
                draw_pixel(x+j, y+i, c);
}

void draw_digits(int16_t x, int16_t y, uint16_t n, uint8_t digits, color c)
{
    draw_box((point){x, y}, digits * 4, 5, draw_color_background(c));

    for (int i = 0; i < digits; ++i, n /= 10)
        digit(x + 4*(digits-i-1), y, numbers[n % 10], c);
}

void draw_clean(point p, color c)
{
    draw_box(arena_to_pixel(p), 4, 4, draw_color_background(c));
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
                        draw_pixel(p.x+j, p.y+i, c);
        return;
    }
    if (rt == ROTT_CORNERS && rot == ROT_DOWN)
    {
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                if (si.rows[3-j] & (1 << (4+i)))
                    draw_pixel(p.x+j, p.y+i, c);
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
                draw_pixel(p.x+j, p.y+i, c);
        }
}

void draw_points(int n, color c)
{
    if(n >= 0)
        draw_digits(L_POINTS_X, L_POINTS_Y, n, 4, c);
}

void draw_cls(color c)
{
    boxColor(screen, 0, 0, S_SCREEN_X * S_ZOOM_X - 1, S_SCREEN_Y * S_ZOOM_Y - 1, draw_color_background(c));
}

void draw_init(int points, color c)
{
    draw_cls(c);

    draw_box((point){0, 6}, S_ARENA_X*4+4, 1, c);

    draw_box((point){0, 9},                S_ARENA_X*4+4, 1, c);
    draw_box((point){0, 9},                1, S_ARENA_Y*4+4, c);
    draw_box((point){0, S_SCREEN_Y - 1},   S_ARENA_X*4+4, 1, c);
    draw_box((point){S_SCREEN_X - 1, 9},   1, S_ARENA_Y*4+4, c);

    draw_points(points, c);
}

void draw_update(void)
{
//    static int n = 0;
//    printf("Update #%d\n", n++);

    SDL_Flip(screen);
}

void draw_img(const spic * pic, color c)
{
    for (int i = 0; i < S_IMG_Y; ++i)
        for (int j = 0; j < S_IMG_X; ++j)
            if (pic->img[i][j])
                draw_pixel(j + 5, i, c);
}



