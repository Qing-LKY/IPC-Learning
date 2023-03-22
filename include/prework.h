#ifndef PREWORK_H
#define PREWORK_H

#include "ds.h"

extern status_t S;

int connect(const char *path, int reset);
int clear_exitmsg();
int set_sighandler();
int run_listener();

#endif