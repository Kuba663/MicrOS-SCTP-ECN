#include "micros_socket.h"

int socket(int domain, int type, int protocol)
{
    return micros_interrupt_3a(SYSCALL_SOCKET, domain, type, protocol);
}

int bind(int s, struct sockaddr *my_addr, socklen_t addrlen)
{
    return micros_interrupt_3a(SYSCALL_BIND, s, my_addr, addrlen);
}

ssize_t recv(int s, void *buf, size_t len, int flags)
{
    return 0;
}

ssize_t recvfrom(int s, void *buf, size_t len, int flags,
                 struct sockaddr *from, socklen_t *fromlen)
{
    struct recv_params params = {
        .s = s,
        .buf = buf,
        .len = len,
        .flags = flags,
        .from = from,
        .fromlen = fromlen};

    ssize_t ret;

    while (!(ret = micros_interrupt_1a(SYSCALL_RECVFROM, &params)))
        ;
    return ret;
}

ssize_t sendto(int s, const void *buf, size_t len,
               int flags, const struct sockaddr *to,
               socklen_t tolen)
{
    struct sendto_params params = {
        .s = s,
        .buf = buf,
        .len = len,
        .flags = flags,
        .to = to,
        .tolen = tolen
    };

    ssize_t ret;

    while (!(ret = micros_interrupt_1a(SYSCALL_SENDTO, &params)))
        ;
    return ret;

}