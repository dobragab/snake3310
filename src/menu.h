#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include "main.h"

typedef enum
{
    MENU_NONE,
    MENU_QUIT,
    MENU_OK,
    MENU_CANCEL,
    MENU_CONT,

    MENU_COUNT,

} MenuResult;

typedef MenuResult (*MenuFunc)();

typedef struct
{
    const char * name;
    MenuFunc func;

} MenuItem;

const MenuItem * ShowMenu(bool cont);
MenuResult Maze();

#endif // MENU_H_INCLUDED
