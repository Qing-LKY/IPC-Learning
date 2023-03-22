#include "ds.h"
#include "libmsg.h"

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <signal.h>
#include <pthread.h>
#include <errno.h>

status_t S;

void *listener(void *args) {
    char buf[SIZE];
    int msqid = *(int *)args;
    while (recv_msg(msqid, EXIT_MSG, buf) == -1);
    kill(0, SIGINT);
    pthread_exit(NULL);
}

void sig_handle(int signo) {
    if (signo == SIGINT || signo == SIGTERM) {
        int re = send_msg(S.msqid, EXIT_MSG, NULL);
        if (re == -1) {
            puts("Failed to send exit msg!");
            exit(1);
        } else {
            puts("Exit successfully!");
            exit(0);
        }
    }
}

int connect(const char *path, int reset) {
    int ret; key_t key;
    // generate key
    ret = gen_key(path, &key);
    if (ret == -1) return -1;
    // reset queue
    if (reset) {
        puts("Flag RESET is ON. Try to remove exist queue...");
        ret = msgget(key, IPC_EXCL);
        if (ret != -1) {
            ret = remove_queue(ret);
            if (ret == -1) return perror("ipcrm"), -1;
        }
        puts("Reset successfully!");
    }
    // connect or create msg queue
    ret = connect_queue(key, &S.msqid);
    if (ret == -1) return -1;
    return 0;
}

int clear_exitmsg() {
    static char buf[SIZE];
    puts("Clear EXIT_MSG...");
    while (recv_msg(S.msqid, EXIT_MSG, buf) != -1);
    return 0;
}

int set_sighandler() {
    sighandler_t ret;
    ret = signal(SIGINT, sig_handle);
    if (ret == SIG_ERR) return perror("signal"), -1;
    ret = signal(SIGTERM, sig_handle);
    if (ret == SIG_ERR) return perror("signal"), -1;
    return 0;
}

int run_listener() {
    int ret;
    pthread_t tid;
    ret = pthread_create(&tid, NULL, listener, (void *)&S.msqid);
    if (ret != 0) return perror("listener"), -1;
    return 0;
}