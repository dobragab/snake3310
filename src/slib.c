#include "slib.h"

jmp_buf error_buffer;

void debugmalloc(const void * ptr, const char * msg)
{
    if (ptr == NULL)
    {
        printf("Allocation was unsuccessful: %s\n", msg);
        rage_quit();
    }
}

void rage_quit(void)
{
    longjmp(error_buffer, 1);
}
// Itt jártam, Jani, 2015.09.22. 1:46:43

Uint32 timer_callback(Uint32 ms, void *param)
{
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);

    return ms;
}

void SDL_ToggleTimer(SDL_TimerID* timer)
{
    if(timer == NULL)
        return;

    if(*timer)
    {
        SDL_RemoveTimer(*timer);
        *timer = 0;
    }
    else
        *timer = SDL_AddTimer(SPEEDS[LEVEL-1], timer_callback, NULL);
}
