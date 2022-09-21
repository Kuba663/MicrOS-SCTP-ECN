/*
    @JakubPrzystasz
    Created: 17.02.2021
    Modify:
*/
#ifndef ipv4_protocol
#define ipv4_protocol

#include <inet/ethernet.h>
#include <inet/ipv4.h>
#include <network/network_utils.h>
#include <network/network_manager.h>

#include "../icmp/icmp.h"
#include "../dhcp/dhcp.h"
#include "../udp/udp.h"
#include "../tcp/tcp.h"



//! ipv4_process_packet
/*
    Process packet IPv4
*/
void ipv4_process_packet(nic_data_t *data);

void ipv4_checksum(ipv4_packet_t *packet);

void ipv4_init();

nic_data_t *ipv4_create_packet(net_device_t *device, uint8_t protocol, ipv4_addr_t dst, uint32_t data_size);

uint32_t ipv4_send_packet(nic_data_t *data);

#endif