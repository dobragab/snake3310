#ifndef SITEM_H_INCLUDED
#define SITEM_H_INCLUDED

#include "main.h"

typedef enum /// part
{
    PART_HEAD,
    PART_BITE,
    PART_BODY,
    PART_BODY_FOOD,
    PART_CORNER,
    PART_CORNER_FOOD,
    PART_TAIL,

    PART_COUNT,

} part;

typedef union /// sitem
{
    uint32_t item;    uint8_t rows[4];

} sitem;

typedef struct /// snum
{
    uint8_t col[3];

} snum;

typedef struct /// smaze
{
    uint32_t rows[9]; // used only first 20 bits of 32
    point sp;
    const char * name;

} smaze;

typedef struct /// spic
{
    char img[S_IMG_Y][S_IMG_X];

} spic;

extern const snum numbers[];
extern const sitem bugs[];
extern const sitem parts[];
extern const sitem berry;

extern const smaze mazes[];

extern const spic intro[];

#endif // SITEM_H_INCLUDED
