/*
    @JakubPrzystasz
    Created: 13.02.2021
    Modified: 17.02.2021
*/
#ifndef network_utils
#define network_utils

#include <stdint.h>
#include <stdbool.h>

//! __uint8_flip
/*
    Flip bits in 8 bit-wide field
*/
uint8_t __uint8_flip(uint8_t value);
//! __uint16_flip
/*
    Flip bits in 16 bit-wide field
*/
uint16_t __uint16_flip(uint16_t value);

//! __uint32_flip
/*
    Flip bits in 32 bit-wide field
*/
uint32_t __uint32_flip(uint32_t value);

//! __set_mac_addr
/*
    Sets MAC addr
*/
void __set_mac_addr(uint8_t *mac_addr, uint8_t oct1, uint8_t oct2, uint8_t oct3, uint8_t oct4, uint8_t oct5, uint8_t oct6);

//! __set_ipv4_addr
/*
    Sets IP addr
*/
void __set_ipv4_addr(uint8_t *ip_addr, uint8_t oct1, uint8_t oct2, uint8_t oct3, uint8_t oct4);

//! __checksum
/*
    One's compliement checksum
*/
uint16_t __checksum(uint16_t *data, uint16_t len);

#endif