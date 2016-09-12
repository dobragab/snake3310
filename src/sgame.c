#include "main.h"

static bool active = false;
static color game_color = C_PIXEL;

static MenuResult StartGame(void)
{
    SDL_Event ev;
    MenuResult result = MENU_CONT;

    SDL_TimerID timer = SDL_ADDTIMER(SPEEDS[LEVEL-1]);

    if (!active)
    {
        maze_import(&mazes[MAZE]);
        snakes_new(PLAYERS, SNAKE_LENGTH);

        food_new(FOOD * PLAYERS, game_color);
        bug_new(game_color);
        active = true;
    }

    draw_init(snakes_score(), game_color);

    SDL_PUSHEVENT(SDL_INIT);

    bool quit = false;
    bool screenchanged = false;

    while (!quit)
    {
        SDL_WaitEvent(&ev);

        screenchanged = false;

        switch (ev.type)
        {
            case SDL_INIT:
            {
                screenchanged = true;

                if(PLAYERS == 1)
                    maze_draw();
                food_draw();
                snakes_draw();

                break;
            }
            case SDL_TICK:
            {
                screenchanged = true;

                snakes_process();

                if (!snakes_alldying())
                    bug_process();

                draw_points(snakes_score(), game_color);

                if (snakes_alldead())
                {
                    result = MENU_OK;
                    quit = true;
                }

                break;
            }
            case SDL_KEYDOWN:
            {
                screenchanged = true;

                SDLKey key = ev.key.keysym.sym;

                switch (key)
                {
                    case SDLK_SPACE:
                        SDL_ToggleTimer(&timer);
                        break;

                    case SDLK_ESCAPE:
                        result = MENU_CONT;
                        quit = true;
                        break;

                    default:
                        snakes_turn(key);
                        break;
                }
                break;
            }

            case SDL_QUIT:
                result = MENU_QUIT;
                quit = true;
                break;

            default:
                break;
        }
        if (screenchanged)
            draw_update();
    }

    if (timer)
        SDL_RemoveTimer(timer);

    return result;
}

MenuResult Continue(void)
{
    return StartGame();
}

MenuResult SinglePlayer(void)
{
    FinishGame();
    PLAYERS = 1;
    game_color = C_PIXEL;
    return StartGame();
}

MenuResult MultiPlayer(void)
{
    MenuResult num = MultiNum();
    if(num == MENU_OK)
    {
        set_arena(maze_multi_size(PLAYERS));
        FinishGame();
        game_color = C_WHITE;
        MenuResult gr = StartGame();
        set_arena(maze_multi_size(1));
        return gr;
    }
    return num;
}

void FinishGame(void)
{
    if (!active)
        return;

    snakes_delete();

    food_delete();
    maze_delete();

    active = false;
}

cell cell_contains(point p)
{
    if (food_contains(p))
        return CELL_FOOD;

    if (snakes_contains(p))
        return CELL_SNAKE;

    if (bug_contains(p))
        return CELL_BUG;

    if (PLAYERS == 1 && maze_contains(p))
        return CELL_WALL;

    return CELL_NONE;
}

