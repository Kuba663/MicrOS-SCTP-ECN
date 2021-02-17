/*
    @JakubPrzystasz
    Created: 17.02.2021
    Modify: 
*/
#ifndef ipv4_protocol
#define ipv4_protocol

#include "ipv4_definitions.h"
#include "../../network_utils.h"
#include "../../network_manager.h"

//! ipv4_process_packet
/*
    Process packet IPv4
*/
void ipv4_process_packet(ipv4_packet_t *packet, uint8_t *device_mac);

#endif