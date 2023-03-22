#ifndef DS_H
#define DS_H

#define EXIT_MSG 1
#define SIZE 50

#define DEF_PERM 0666

typedef struct {
    int msqid;
    int ready;
} status_t;

typedef struct {
    long mtype;
    char mtext[SIZE];
} msgbuf_t;

typedef void (*sighandler_t)(int);

#endif