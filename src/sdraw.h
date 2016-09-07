#ifndef SDRAW_H_INCLUDED
#define SDRAW_H_INCLUDED

#include "main.h"

enum
{
    S_SCREEN_X = S_ARENA_X * 4 + 4,  /// 84 x 49
    S_SCREEN_Y = S_ARENA_Y * 4 + 13,

    L_POINTS_X = 1,
    L_POINTS_Y = 0,

    L_TIMER_X = S_SCREEN_X - 8,
    L_TIMER_Y = 0,

    L_BUG_X = S_SCREEN_X - 18,
    L_BUG_Y = 1,

    L_ARENA_X = 1,
    L_ARENA_Y = 10,
};

extern const color C_PIXEL;
extern const color C_RED;
extern const color C_BGND;

extern const int SPEEDS[];

void draw_small_text(const char * text, point p, bool selected);
void draw_narrow_text(const char * text, point p, bool selected);
void draw_big_text(const char * text, point p, bool selected);

void draw_init();
void draw_pixel(int16_t x, int16_t y);
void draw_pixel_c(int16_t x, int16_t y, color c);
void draw_box(point p, int16_t w, int16_t h, color c);
void draw_digits(int16_t x, int16_t y, uint16_t n, uint8_t digits);
void draw_item(sitem si, point p, rotation rot, rot_type rt);
void draw_bug(sitem si, point p, rotation rot, rot_type rt);
void draw_clean(point p);
void draw_update();
void draw_points(int n);
void draw_cls();
void draw_img(const spic * pic);
void screen_init(point p);

#endif // SDRAW_H_INCLUDED
