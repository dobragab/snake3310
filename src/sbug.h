#ifndef SBUG_H_INCLUDED
#define SBUG_H_INCLUDED

#include "main.h"

void bug_new(color c);
void bug_process(void);
int bug_eat(void);
int bug_count(void);
bool bug_contains(point p);
void bug_generate(void);

#endif // SBUG_H_INCLUDED
