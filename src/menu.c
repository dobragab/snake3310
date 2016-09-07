#include "main.h"

static const MenuItem items[] =
{
    {
        .name = "Continue",
        .func = Continue,
    }, {
        .name = "Single player",
        .func = SinglePlayer,
    }, {
        .name = "Level",
        .func = Level,
    }, {
        .name = "Zoom",
        .func = Zoom,
    }, {
        .name = "Mazes",
        .func = Maze,
    }, {
        .name = "Top score",
        .func = TopScore,
    }, {
        .name = "Instructions",
        .func = Instructions,
    },
};

enum
{
    ITEMS_NO = 6,
    ITEMS_SHOWN = 4,
    ITEMS_W = S_SCREEN_X - 6,
    ITEMS_H = 10,

    L_SBAR_X = S_SCREEN_X - 3,
    L_SBAR_Y = 9,

    SBAR_W = 3,
    SBAR_H = 7,
};

static void MenuDraw(const char *lines[], int no, int top, int selected)
{
    draw_cls();

    point sp = {0, 8};

    for (int i = 0; i < ITEMS_SHOWN; ++i)
    {
        int j = i+top;
        point tsp = {sp.x + 2, sp.y + 1};

        int index = j >= no ? j-no : j;
        if (i == selected)
        {
            draw_box(sp, ITEMS_W, ITEMS_H, C_PIXEL);
            draw_small_text(lines[index], tsp, true);
        }
        else
            draw_small_text(lines[index], tsp, false);

        sp.y += 10;
    }

    int n = top+selected;
    if (n >= no)
        n -= no;

    char buf[8];
    sprintf(buf, "8-1-%d", n+1 % 10);
    draw_small_text(buf, (point){S_SCREEN_X - 28, 0}, false);

    int vbary = (ITEMS_SHOWN * ITEMS_H - SBAR_H) * n / (no-1) + L_SBAR_Y;

    draw_box((point){L_SBAR_X, L_SBAR_Y}, 1, ITEMS_SHOWN * ITEMS_H, C_PIXEL);
    draw_box((point){L_SBAR_X, vbary+1}, SBAR_W - 1, SBAR_H - 2, C_BGND);
    draw_box((point){L_SBAR_X + SBAR_W-1, vbary + 1}, 1, SBAR_H - 2, C_PIXEL);
    draw_box((point){L_SBAR_X, vbary}, SBAR_W-1, 1, C_PIXEL);
    draw_box((point){L_SBAR_X, vbary+SBAR_H-1}, SBAR_W-1, 1, C_PIXEL);

    draw_update();
}

static int Menu(const char *lines[], int no, int * restrict top, int * restrict selected)
{
    MenuDraw(lines, no, *top, *selected);

    SDL_Event ev;
    bool quit = false, screenchanged;

    while (!quit)
    {
        screenchanged = false;
        SDL_WaitEvent(&ev);

        switch(ev.type)
        {
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym)
                {
                    case SDLK_UP:
                        screenchanged = true;

                        (*selected)--;

                        if (*selected < 0)
                        {
                            (*top)--;
                            *selected = 0;
                        }

                        if (*top < 0)
                            *top += no;

                        break;

                    case SDLK_DOWN:
                        screenchanged = true;
                        (*selected)++;

                        if (*selected >= ITEMS_SHOWN)
                        {
                            (*top)++;
                            *selected = ITEMS_SHOWN - 1;
                        }

                        if (*top >= no)
                            *top -= no;

                        break;

                    case SDLK_ESCAPE:
                        return -MENU_CANCEL;
                        break;

                    case SDLK_SPACE:
                    case SDLK_RETURN:
                        quit = true;
                        break;

                    default:
                        break;
                }
                break;

            case SDL_QUIT:
                return -MENU_QUIT;
                break;

            default:
                break;
        }
        if (screenchanged)
            MenuDraw(lines, no, *top, *selected);
    }

    int n = *top+*selected;
    if (n >= no)
        n -= no;

    return n;
}

const MenuItem * ShowMenu(bool cont)
{
    static int top = 0, selected = 0;

    const char * lines[ITEMS_NO - !cont];

    for (int i = 0; i < ITEMS_NO - !cont; ++i)
        lines[i] = items[i + !cont].name;

    int result = Menu(lines, ITEMS_NO - !cont, &top, &selected);

    if (result < 0)
        return NULL;

    return &items[result + !cont];
}

MenuResult Maze()
{
    int top = MAZE, selected = 0;

    const char * lines[MAZES_COUNT];

    for (int i = 0; i < MAZES_COUNT; ++i)
        lines[i] = mazes[i].name;

    int result = Menu(lines, MAZES_COUNT, &top, &selected);

    if (result < 0)
        return -result;

    MAZE = result;

    return MENU_OK;
}
