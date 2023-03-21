#ifndef LIBMSG_H
#define LIBMSG_H

#include <sys/types.h>

int gen_key(const char *path, key_t *key);
int create_queue(key_t key);
int remove_queue(int msqid);
int connect_queue(key_t key, int *msqid);
int send_msg(int msqid, int type, const char *s);
int recv_msg(int msqid, int type, char *buf);

#endif