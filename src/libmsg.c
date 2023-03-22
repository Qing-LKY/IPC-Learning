#include "ds.h"
#include "libmsg.h"
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int gen_key(const char *path, key_t *key) {
    *key = ftok(path, 'a');
    if (errno != 0) return perror("ftok"), -1;
    return 0;
}

int create_queue(key_t key) {
    return msgget(key, IPC_EXCL | IPC_CREAT | DEF_PERM);
}

int remove_queue(int msqid) {
    return msgctl(msqid, IPC_RMID, NULL);
}

int connect_queue(key_t key, int *msqid) {
    int ret;
    ret = msgget(key, IPC_EXCL);
    if (ret == -1) {
        puts("Exist IPC queue not found. Now try to create one.");
        ret = create_queue(key);
        if (ret == -1) {
            perror("msgget");
            return -1;
        }
        puts("Success to create queue!");
    } else {
        puts("Connect to an existing IPC queue!");
    }
    *msqid = ret;
    printf("-- msqid: %d --\n", *msqid);
    return 0;
}

int send_msg(int msqid, int type, const char *s) {
    static msgbuf_t tmp;
    int len = 0, re;
    if (type != EXIT_MSG) {
        len = strlen(s);
        if (len >= SIZE) {
            printf("Too long message, has been cut to %d bytes.\n", SIZE);
            len = SIZE - 1;
            memcpy(tmp.mtext, s, len);
        } else strcpy(tmp.mtext, s);
    }
    tmp.mtype = type;
    re = msgsnd(msqid, &tmp, len, IPC_NOWAIT);
    // printf("%ld %s %d\n", tmp.mtype, tmp.mtext, len);
    if (re == -1) perror("msgsnd");
    return re == -1 ? -1 : len;
}

int recv_msg(int msqid, int type, void *buf) {
    int re;
    re = msgrcv(msqid, buf, SIZE, type, IPC_NOWAIT);
    // if (re == -1) {
    //     if (errno == ENOMSG) printf("Message of type %d not found!\n", type);
    //     else perror("msgrcv");
    // }
    return re;
}