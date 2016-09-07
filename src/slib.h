#ifndef SLIB_H_INCLUDED
#define SLIB_H_INCLUDED

#include <stdint.h>

typedef uint32_t color;

#include "main.h"

extern jmp_buf error_buffer;

#define DEBUGMALLOC(ptr) debugmalloc(ptr, #ptr);
void debugmalloc(const void*, const char*);
Uint32 timer_callback(Uint32 ms, void *param);
void rage_quit();

enum
{
    SDL_TICK = SDL_USEREVENT,
    SDL_INIT,
};

#define SDL_PUSHEVENT(t) SDL_PushEvent((SDL_Event[]){{.type = t}})
#define SDL_ADDTIMER(t) SDL_AddTimer(t, timer_callback, NULL)

#endif // SLIB_H_INCLUDED
