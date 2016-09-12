#include "main.h"

#include <limits.h>

#include "iniparser.h"

static const char * ININAME = "config.ini";
static const double zoom_ratio = 1.2;
static int ZOOM = 6;

int LEVEL = 5;
int MAZE = 0;
int PLAYERS = 1;

size S_ZOOM = { 6, 7 };

static void SetZooms(void)
{
    S_ZOOM.x = ZOOM;
    S_ZOOM.y = lround(zoom_ratio * ZOOM);
}

void LoadConfig(void)
{
    dictionary * inifile = iniparser_load(ININAME);
    if (!inifile)
        return;

    LEVEL = iniparser_getint(inifile, "config:level", LEVEL);
    MAZE  = iniparser_getint(inifile, "config:maze" , MAZE);
    ZOOM  = iniparser_getint(inifile, "config:zoom" , ZOOM);

    SetZooms();

    iniparser_freedict(inifile);
}

static void iniparser_setint(dictionary * ini, const char * entry, int val)
{
    static const int bufsize = ((CHAR_BIT * sizeof(int) + 3.0 - 1) / 3.0) + 2;

    char buffer[bufsize];
    sprintf(buffer, "%d", val);

    iniparser_set(ini, entry, buffer);
}

void SaveConfig(void)
{
    dictionary * inifile = iniparser_load(ININAME);
    if (!inifile)
    {
        FILE * fp = fopen(ININAME, "wt");
        fclose(fp);

        inifile = iniparser_load(ININAME);

        if (!inifile)
            return;
    }

    iniparser_set(inifile, "config", NULL);
    iniparser_setint(inifile, "config:level", LEVEL);
    iniparser_setint(inifile, "config:maze" , MAZE);
    iniparser_setint(inifile, "config:zoom" , ZOOM);

    FILE * fp = fopen(ININAME, "wt");

    iniparser_dump_ini(inifile, fp);

    fclose(fp);

    iniparser_freedict(inifile);
}


MenuResult TopScore(void)
{
    draw_cls(C_PIXEL);

    draw_big_text("Top score:", (point){0, 2}, C_PIXEL);

    char buf[10] = {0};
    sprintf(buf, "%d", 1309);

    draw_big_text(buf, (point){0, 17}, C_PIXEL);

    draw_update();

    SDL_Event ev;
    bool quit = false;

    while (!quit)
    {
        SDL_WaitEvent(&ev);

        switch(ev.type)
        {
        case SDL_QUIT:
            return MENU_QUIT;
            break;
        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_ESCAPE:
            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
            case SDLK_SPACE:
            case SDLK_RETURN:
                quit = true;
                break;

            default:
                break;
            }
        }
    }

    return MENU_CANCEL;
}

static void level_draw(const char * text, int lvl)
{
    draw_cls(C_PIXEL);
    draw_small_text(text, (point){3, 0}, C_PIXEL);


    point sp = {6, S_SCREEN.y - 11};

    for (int i = LEVEL_MIN; i <= LEVEL_MAX; ++i)
    {
        draw_box(sp, (size){4, 1}, C_PIXEL);
        draw_box((point){sp.x + 4, sp.y - 6 - 2*i}, (size){1, 6 + 2*i + 1}, C_PIXEL);

        sp.x += 8;
    }

    sp = (point){5, S_SCREEN.y - 18};

    for (int i = LEVEL_MIN; i <= lvl; ++i)
    {
        draw_box(sp, (size){4, 6 + 2*i}, C_PIXEL);

        sp.x += 8;
        sp.y -= 2;
    }

    draw_update();
}

static MenuResult LevelChooser(const char * text, int * LVL, int min, int max)
{
    int lvl = *LVL - 1;

    level_draw(text, lvl);

    SDL_Event ev;
    bool quit = false, screenchanged;

    while (!quit)
    {
        SDL_WaitEvent(&ev);

        screenchanged = false;

        switch(ev.type)
        {
            case SDL_QUIT:
                return MENU_QUIT;
                break;
            case SDL_KEYDOWN:
                switch (ev.key.keysym.sym)
                {
                    case SDLK_RIGHT:
                    case SDLK_UP:
                        screenchanged = true;
                        lvl++;
                        if(lvl > max)
                            lvl = max;
                        break;

                    case SDLK_LEFT:
                    case SDLK_DOWN:
                        screenchanged = true;
                        lvl--;
                        if(lvl < min)
                            lvl = min;
                        break;

                    case SDLK_SPACE:
                    case SDLK_RETURN:
                        *LVL = lvl + 1;
                        return MENU_OK;
                        break;

                    case SDLK_ESCAPE:
                        quit = true;
                        break;

                    default:
                        break;
                }
        }

        if (screenchanged)
            level_draw(text, lvl);
    }

    return MENU_CANCEL;
}


MenuResult Level(void)
{
    return LevelChooser("Level:", &LEVEL, LEVEL_MIN, LEVEL_MAX);
}

MenuResult Zoom(void)
{
    MenuResult rslt = LevelChooser("Zoom:", &ZOOM, LEVEL_MIN, LEVEL_MAX);

    if (rslt == MENU_OK)
    {
        SetZooms();
        screen_init();
    }

    return rslt;
}

static void ins_draw(char *lines[], int start, int n)
{
    draw_cls(C_PIXEL);

    point sp = {0, 2};
    int diff = 9;

    for (int i = start; i < start+n; ++i)
    {
        draw_narrow_text(lines[i], sp, C_PIXEL);
        sp.y += diff;
    }

    draw_update();
}

MenuResult Instructions(void)
{
    char *lines[] =
    {
        "Make the snake",
        "grow longer by",
        "directing it to the",
        "food. Use the keys",
        "2, 4, 6 and 8. You",
        "cannot stop the",
        "snake or make it go",
        "backwards. Try not",
        "to hit the walls or",
        "the tail.",
    };

    int page = 0;

    ins_draw(lines, 5*page, 5);

    SDL_Event ev;
    bool quit = false, screenchanged;

    while (!quit)
    {
        SDL_WaitEvent(&ev);

        screenchanged = false;

        switch(ev.type)
        {
        case SDL_QUIT:
            return MENU_QUIT;
            break;

        case SDL_KEYDOWN:
            switch (ev.key.keysym.sym)
            {
            case SDLK_ESCAPE:
                quit = true;
                break;

            case SDLK_UP:
            case SDLK_DOWN:
            case SDLK_LEFT:
            case SDLK_RIGHT:
            case SDLK_SPACE:
            case SDLK_RETURN:
                screenchanged = true;
                page = !page;
                break;

            default:
                break;
            }
        }

        if (screenchanged)
            ins_draw(lines, 5*page, 5);
    }

    return MENU_CANCEL;
}

MenuResult MultiNum(void)
{
    PLAYERS = 2;
    MenuResult result = LevelChooser("Players:", &PLAYERS, 1, SNAKES_MAX - 1);
    return result;
}

