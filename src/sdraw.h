#ifndef SDRAW_H_INCLUDED
#define SDRAW_H_INCLUDED

#include "main.h"

extern int S_SCREEN_X;
extern int S_SCREEN_Y;

extern int L_POINTS_X;
extern int L_POINTS_Y;

extern int L_TIMER_X;
extern int L_TIMER_Y;

extern int L_BUG_X;
extern int L_BUG_Y;

extern int L_ARENA_X;
extern int L_ARENA_Y;

#define C_PIXEL ((color)(0x000000FF))
#define C_WHITE ((color)(0xFFFFFFFF))
#define C_RED   ((color)(0xFF0000FF))
#define C_BGND  ((color)(0xB2BD08FF))

void set_arena(size s);
void screen_init(void);


extern const int SPEEDS[];

void draw_small_text(const char * text, point p, bool selected);
void draw_narrow_text(const char * text, point p, bool selected);
void draw_big_text(const char * text, point p, bool selected);

color draw_color_background(color front_color);
void draw_init(int points, color c);
void draw_pixel(int16_t x, int16_t y, color c);
void draw_box(point p, int16_t w, int16_t h, color c);
void draw_digits(int16_t x, int16_t y, uint16_t n, uint8_t digits, color c);
void draw_item(sitem si, point p, rotation rot, rot_type rt, color c);
void draw_bug(sitem si, point p, rotation rot, rot_type rt, color c);
void draw_clean(point p, color c);
void draw_update(void);
void draw_points(int n, color c);
void draw_cls(color c);
void draw_img(const spic * pic, color c);

#endif // SDRAW_H_INCLUDED
