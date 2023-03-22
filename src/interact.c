#include "ds.h"
#include "libmsg.h"
#include "prework.h"
#include "interact.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include <readline/readline.h>
#include <readline/history.h>

int parseline(char *s, char argv[][SIZE]) {
    int len, i, j, c = 0, e;
    len = strlen(s);
    argv[0][0] = argv[1][0] = argv[2][0] = 0;
    for (i = 0; i < len; i++) {
        if (!isspace(s[i])) {
            if (c != 2) {
                for (j = i; j < len && !isspace(s[j]); j++);
                e = j - i >= SIZE ? SIZE - 1 : j - i;
                memcpy(argv[c], s + i, e);
                argv[c][e] = 0;
                c++;
                i = j;
            } else {
                for (j = len - 1; j > i && isspace(s[j]); j--);
                if (s[i] == '\"') i++;
                if (s[j] != '\"') j++;
                if (j <= i) argv[c][0] = 0;
                else {
                    e = j - i >= SIZE ? SIZE - 1 : j - i;
                    memcpy(argv[c], s + i, e);
                    argv[c][e] = 0;
                    c++;
                    break;
                }
            }
        }
    }
    return 0;
}

int match_cmd(const char *s) {
    if (strcmp(s, "help") == 0) return 0;
    if (strcmp(s, "send") == 0) return 1;
    if (strcmp(s, "recv") == 0) return 2;
    return -1;
}

void display_help() {
    puts("Support following command:");
    puts(" help -- show this information");
    puts(" send <mtype> <string> -- sendmsg");
    puts(" recv <mtype> -- rcvmsg");
}

int copy_number(int *cnf, const char *arg) {
    char *endptr;
    errno = 0;
    // set 0 to auto choose 10, 8 or 16
    *cnf = strtol(arg, &endptr, 0);
    // something wrong when convert
    if (errno != 0 || *endptr != 0) return 1;
    return 0;
}

void do_sendmsg(char *stype, char *str) {
    int mtype, ret;
    ret = copy_number(&mtype, stype);
    if (ret != 0) {
        puts("Bad mtype number!");
        return;
    }
    if (mtype == EXIT_MSG) {
        puts("Type 1 is occupied by EXIT_MSG!");
        return;
    }
    ret = send_msg(S.msqid, mtype, str);
    if (ret != -1) puts("Send successfully!");
}

void do_recvmsg(char *stype) {
    static msgbuf_t buf;
    int mtype, ret;
    ret = copy_number(&mtype, stype);
    if (ret != 0) {
        puts("Bad mtype number!");
        return;
    }
    buf.mtext[0] = 0;
    ret = recv_msg(S.msqid, mtype, (void *)&buf);
    if (ret == -1) {
        // if (errno == ENOMSG) printf("Message of type %d not found!\n", mtype);
        // else 
        perror("msgrcv");
    } else {
        printf("Recv: ");
        puts(buf.mtext);
    }
}

void interactor() {
    // limit: 50 bytes for each args
    static char argv[3][SIZE];
    while(1) {
        char *s = readline("# ");
        parseline(s, argv);
        int opt = match_cmd(argv[0]);
        switch (opt) {
            case 0: display_help(); break;
            case 1: do_sendmsg(argv[1], argv[2]); break;
            case 2: do_recvmsg(argv[1]); break;
            default: {
                puts("Unknown command. Type `help' for more info.");
                break;
            }
        }
        if (opt != -1) add_history(s);
        free(s);
    }
}