#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <stdbool.h>
#include <stdlib.h>
#include <setjmp.h>
#include <time.h>
#include <math.h>

#include <SDL.h>
#include <SDL_gfxPrimitives.h>
#include <SDL_ttf.h>

#define SUCCESS 0
//#define DEBUG

#if defined(__WIN32__) && defined(DEBUG)
#define WINDEBUG
#endif

#ifdef WINDEBUG
#define PRINT_D(s) printf("%s = %d\n", #s, s)
#else
#define PRINT_D(s)
#endif // WINDEBUG

#ifndef DEBUG
#define printf(...)
#endif

#ifdef DEBUG
#include "debugmalloc.h"
#endif // DEBUG

#include "nokia-fonts.h"

#include "menu.h"

#include "sopt.h"
#include "slib.h"
#include "sdata.h"
#include "sitem.h"
#include "snake.h"
#include "sdraw.h"
#include "sfood.h"
#include "sbug.h"
#include "smaze.h"
#include "sgame.h"
#include "sintro.h"


#endif // MAIN_H_INCLUDED
