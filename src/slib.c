#include "slib.h"

jmp_buf error_buffer;

void debugmalloc(const void * ptr, const char * msg)
{
    if (ptr == NULL)
    {
        printf("Allocation was unsuccessful: %s\n", msg);
        longjmp(error_buffer, 1);
    }
}

void rage_quit()
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
