#include "main.h"

int main (int argc, char *argv[])
{
if (setjmp (error_buffer) == SUCCESS)
{
#ifdef WINDEBUG
    freopen("CON", "w", stdout);
    freopen("CON", "w", stderr);
#endif

#ifndef DEBUG
    srand(time(NULL));
#endif // DEBUG

#ifdef DEBUG
    debugmalloc_naplofajl("_memory_dump.txt");
#endif // DEBUG

    LoadConfig();

    SDL_Init (SDL_INIT_EVERYTHING);
    screen_init();

    PlayIntro();

    bool quit = false;
    bool cont = false;
    while (!quit)
    {
        const MenuItem * selected = ShowMenu(cont);

        if (selected == NULL)
            break;

        MenuResult result = selected->func();

        if (result == MENU_OK)
        {
            FinishGame();
            cont = false;
        }
        if (result == MENU_CONT)
            cont = true;

        if (result == MENU_QUIT)
            quit = true;
    }

    longjmp(error_buffer, 1);
}
else /// ERROR or normal terminating
{
    FinishGame();

    SaveConfig();

    SDL_Quit();

#ifdef DEBUG
    debugmalloc_dump();
#endif // DEBUG
}
    return 0;
}
