#include "main.h"

typedef union
{
    point p;
    uint32_t hash;

} coord;

typedef struct binnode_s
{
    coord c;
    struct binnode_s *left, *right;
} binnode;

typedef struct
{
    point size, sp;
    binnode * root;

} bintree;

static bintree maze = { .size = {0, 0}, .root = NULL };

static binnode * binnode_add(binnode * node, coord c)
{
    if (node == NULL)
    {
        node = (binnode*) malloc(sizeof(binnode));
        debugmalloc(node, "Binary-tree node");

        node->c = c;
        node->left = NULL;
        node->right = NULL;
    }
    else if (c.hash < node->c.hash)
        node->left = binnode_add(node->left, c);
    else if (c.hash > node->c.hash)
        node->right = binnode_add(node->right, c);

    return node;
}

static void draw_wall(point pt, int right, int down)
{
    point p = arena_to_pixel(pt);
    point q = (point) { .x = p.x + 1 - right, .y = p.y + 1 - down };
    draw_box(q, (size){2, 2}, C_PIXEL);
}

static void binnode_draw(const binnode * node)
{
    if (node == NULL)
        return;

    draw_wall(node->c.p, 0, 0);

    point right = (point){.x = node->c.p.x + 1, .y = node->c.p.y};
    point down = (point){.x = node->c.p.x, .y = node->c.p.y + 1};

    if (maze_contains(right))
        draw_wall(right, 2, 0);
    if (maze_contains(down))
        draw_wall(down, 0, 2);

    binnode_draw(node->left);
    binnode_draw(node->right);
}

static bool binnode_find(const binnode * node, coord c)
{
    if (node == NULL)
        return false;

    if (c.hash < node->c.hash)
        return binnode_find(node->left, c);
    if (c.hash > node->c.hash)
        return binnode_find(node->right, c);

    return true;
}

static void binnode_delete(binnode * node)
{
    if (node == NULL)
        return;

    binnode_delete(node->left);
    binnode_delete(node->right);

    free(node);
}

void maze_import(const smaze * m)
{
    maze.sp = m->sp;
    maze.size = (point){20, 9};

    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 20; ++j)
            if (m->rows[i] & (1 << (30-j)))
            {
                coord c = {.p = {.x = j, .y = i} };
                maze.root = binnode_add(maze.root, c);
            }
}

void maze_draw(void)
{
    binnode_draw(maze.root);
}

point maze_sp(void)
{
    return maze.sp;
}

bool maze_contains(point p)
{
    if (p.x < 0 || p.y < 0 || p.x >= maze.size.x || p.y >= maze.size.y)
        return false;

    return binnode_find(maze.root, (coord){.p = p});
}

void maze_delete(void)
{
    binnode_delete(maze.root);
    maze = (bintree){.size = {0, 0}, .root = NULL };
}

size maze_multi_size(int num)
{
    double ratio = sqrt(num);
    return (size){ .x = S_ARENA_X1 * ratio, .y = S_ARENA_Y1 * ratio };
}

