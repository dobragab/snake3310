#include "main.h"

static snake * s1 = NULL;
static bool active = false;

static MenuResult StartGame()
{
    SDL_Event ev;
    MenuResult result = MENU_CONT;

    SDL_TimerID timer = SDL_ADDTIMER(SPEEDS[LEVEL]);

    if (!active)
    {
        maze_import(&mazes[MAZE]);
        s1 = snake_new(maze_sp(), SNAKE_LENGTH, ROT_LEFT);

        food_new(FOOD);
        bug_new();
        active = true;
    }

    draw_init(snake_score(s1));

    SDL_PUSHEVENT(SDL_INIT);

    bool quit = false, screenchanged;
    while (!quit)
    {
        SDL_WaitEvent(&ev);

        screenchanged = false;

        switch (ev.type)
        {
            case SDL_INIT:
            {
                screenchanged = true;

                maze_draw();
                food_draw();
                snake_draw(s1);

                break;
            }
            case SDL_TICK:
            {
                screenchanged = true;

                snake_process(s1);

                if (!snake_isdying(s1))
                    bug_process();

                draw_points(snake_score(s1));

                if (snake_isdead(s1))
                {
                    result = MENU_OK;
                    quit = true;
                }

                break;
            }
            case SDL_KEYDOWN:
            {
                screenchanged = true;

                switch (ev.key.keysym.sym)
                {
                    case SDLK_UP:
                        snake_turn(s1, ROT_UP);
                        break;
                    case SDLK_DOWN:
                        snake_turn(s1, ROT_DOWN);
                        break;
                    case SDLK_RIGHT:
                        snake_turn(s1, ROT_RIGHT);
                        break;
                    case SDLK_LEFT:
                        snake_turn(s1, ROT_LEFT);
                        break;

                    case SDLK_SPACE:
                        SDL_ToggleTimer(&timer);
                        break;

                    case SDLK_ESCAPE:
                        result = MENU_CONT;
                        quit = true;
                        break;

                    default:
                        break;
                }
                break;
            }

            case SDL_QUIT:
                result = MENU_QUIT;
                quit = true;
        }
        if (screenchanged)
            draw_update();
    }

    if (timer)
        SDL_RemoveTimer(timer);

    return result;
}

MenuResult Continue()
{
    return StartGame();
}

MenuResult SinglePlayer()
{
    FinishGame();

    return StartGame();
}


void FinishGame()
{
    if (!active)
        return;

    snake_delete(s1);

    food_delete();
    maze_delete();

    active = false;
}

cell cell_contains(point p)
{
    if (food_contains(p))
        return CELL_FOOD;

    if (snake_contains(s1, p))
        return CELL_SNAKE;

    if (bug_contains(p))
        return CELL_BUG;

    if (maze_contains(p))
        return CELL_WALL;

    return CELL_NONE;
}

