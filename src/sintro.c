#include "main.h"

void PlayIntro(void)
{
    SDL_Event ev;

    SDL_TimerID timer = SDL_ADDTIMER(SPEEDS[INTRO_SPEED]);

    bool quit = false;
    int frames = 0;

    SDL_PUSHEVENT(SDL_TICK);

    while (!quit)
    {
        SDL_WaitEvent(&ev);

        switch (ev.type)
        {
            case SDL_TICK:
            {
                if (frames == INTRO_LENGTH)
                {
                    quit = true;
                    break;
                }

                draw_cls(C_PIXEL);

                draw_img(&intro[frames], C_PIXEL);

                ++frames;
                break;
            }

            case SDL_QUIT:
                rage_quit();
                break;
            case SDL_KEYDOWN:
                if (ev.key.keysym.sym == SDLK_ESCAPE)
                    quit = true;
                break;

            default:
                break;
        }
        draw_update();
    }
    SDL_RemoveTimer(timer);
}
