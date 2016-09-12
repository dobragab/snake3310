#ifndef SDRAW_H_INCLUDED
#define SDRAW_H_INCLUDED

#include "main.h"

extern size  S_ARENA;
extern size  S_SCREEN;
extern point L_TIMER;
extern point L_BUG;
extern point L_ARENA;

#define C_PIXEL ((color)(0x000000FF))
#define C_WHITE ((color)(0xFFFFFFFF))
#define C_RED   ((color)(0xFF0000FF))
#define C_BGND  ((color)(0xB2BD08FF))

extern const int SPEEDS[];

void set_arena(size s);
void screen_init(void);

void draw_small_text(const char * text, point p, color c);
void draw_narrow_text(const char * text, point p, color c);
void draw_big_text(const char * text, point p, color c);

color draw_color_background(color front_color);
void draw_init(int points, color c);
void draw_pixel(point p, color c);
void draw_box(point p, size s, color c);
void draw_digits(point p, uint16_t n, uint8_t digits, color c);
void draw_item(sitem si, point p, rotation rot, rot_type rt, color c);
void draw_bug(sitem si, point p, rotation rot, rot_type rt, color c);
void draw_clean(point p, color c);
void draw_update(void);
void draw_points(int n, color c);
void draw_cls(color c);
void draw_img(const spic * pic, color c);

#endif // SDRAW_H_INCLUDED
