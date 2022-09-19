#ifndef MICROS_SYS_SYS_SOCKET_H
#define MICROS_SYS_SYS_SOCKET_H

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <inet/inet.h>
#include <micros/types.h>
#include <micros/socket.h>
#include <micros/syscalls.h>
#include "micros_interrupts.h"

struct recv_params
{
    int s;
    void *buf;
    size_t len;
    int flags;
    struct sockaddr *from;
    socklen_t *fromlen;
};

struct sendto_params
{
int s;
const void *buf;
size_t len;
int flags;
const struct sockaddr *to;
socklen_t tolen;
};

int socket(int domain, int type, int protocol);

int bind(int s, struct sockaddr *my_addr, socklen_t addrlen);

ssize_t recv(int s, void *buf, size_t len, int flags);

ssize_t recvfrom(int s, void *buf, size_t len, int flags,
                 struct sockaddr *from, socklen_t *fromlen);

ssize_t sendto(int s, const void *buf, size_t len,
               int flags, const struct sockaddr *to,
               socklen_t tolen);

#endif