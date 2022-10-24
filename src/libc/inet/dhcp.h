/*
    @JakubPrzystasz
    Created: 01.09.2022
    Modified:
*/
#ifndef INET_DHCP_H
#define INET_DHCP_H

#include <stdint.h>

#define DHCP_MAGIC_COOKIE   0x63825363

#define DHCP_NETMASK        0x01
#define DHCP_ROUTER         0x03
#define DHCP_DNS            0x06
#define DHCP_REQUESTED_IP   0x32
#define DHCP_MESSAGE_TYPE   0x35
#define DHCP_DHCP_SERVER    0x36

#define DHCP_DISCOVER       0x01
#define DHCP_OFFER          0x02
#define DHCP_REQUEST        0x03
#define DHCP_ACK            0x05

typedef struct dhcp_message
{
    uint8_t opcode;
    uint8_t htype;
    uint8_t hlen;
    uint8_t hops;
    uint32_t xid;
    uint16_t secs;
    uint8_t flags1: 7;
    uint8_t broadcast_flag: 1;
    uint8_t flags2;
    ipv4_addr_t ciaddr;
    ipv4_addr_t yiaddr;
    ipv4_addr_t siaddr;
    ipv4_addr_t giaddr;
    uint32_t chaddr[4];
    uint32_t sname[16];
    uint32_t file[32];
    uint32_t magic_cookie;
    uint8_t options[68];
} __attribute__((packed)) dhcp_message_t;

#endif