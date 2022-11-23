/*
    @JakubPrzystasz
    Created: 28.07.2021
    Last modified: 25.11.2021
    https://github.com/coderTrevor/MyOS/blob/master/MyOS_1/Drivers/Virtio_Net.h
*/
#ifndef VIRTIO_GENERIC
#define VIRTIO_GENERIC

#include <stdint.h>
#include <string.h>
#include <cpu/dma/dma.h>
#include <memory/heap/heap.h>

//!
/*
    Reference document:
    https://docs.oasis-open.org/virtio/virtio/v1.1/csprd01/virtio-v1.1-csprd01.html
    That header contains definitions for Legacy Interface over PCI
*/

//! Legacy registers layout
/*
    Registers are defined in 4.1.4.8 section of the ref. doc.
*/
#define REG_DEVICE_FEATURES 0x00
#define REG_DRIVER_FEATURES 0x04
#define REG_QUEUE_ADDRESS 0x08
#define REG_QUEUE_SIZE 0x0C
#define REG_QUEUE_SELECT 0x0E
#define REG_QUEUE_NOTIFY 0x10
#define REG_DEVICE_STATUS 0x12
#define REG_ISR_STATUS 0x13

//! Device status field
/*
    Status field values are described in 2.1
*/
/* Resets device */
#define STATUS_RESET_DEVICE 0x00
/* Indicates that the guest OS has found the device and recognized it as a valid virtio device. */
#define STATUS_DEVICE_ACKNOWLEDGE 0x01
/* Indicates that the guest OS knows how to drive the device. Note: There could be a significant (or infinite) delay before setting this bit. For example, under Linux, drivers can be loadable modules. */
#define STATUS_DRIVER_LOADED 0x02
/* Indicates that the driver is set up and ready to drive the device. */
#define STATUS_DRIVER_OK 0x04
/* Indicates that the driver has acknowledged all the features it understands, and feature negotiation is complete. */
#define STATUS_FEATURES_OK 0x08
/* Indicates that the device has experienced an error from which it can’t recover. */
#define STATUS_DEVICE_NEEDS_RESET 0x40
/* Indicates that something went wrong in the guest, and it has given up on the device. This could be an internal error, or the driver didn’t like the device for some reason, or even a fatal error during device operation. */
#define STATUS_DRIVER_FAILED 0x80

//! ISR field
/*
    ISR field values are described in 4.1.5.3 and 4.1.5.4
*/
/* Look through all virtqueues for the device, to see if any progress has been made by the device which requires servicing. */
#define VIRTIO_ISR_VIRTQ_USED 0x01
/* Re-examine the configuration space to see what changed. */
#define VIRTIO_ISR_CONFIG_CHANGED 0x02

// Flags for virtqueue descriptors
/* This marks a buffer as continuing via the next field. */
#define VIRTQ_DESC_F_NEXT 0x01
/* This marks a buffer as device write-only (otherwise device read-only). */
#define VIRTQ_DESC_F_DEVICE_WRITE_ONLY 0x02
#define VIRTQ_DESC_F_DEVICE_READ_ONLY 0x00
/* This means the buffer contains a list of buffer descriptors. */
#define VIRTQ_DESC_F_INDIRECT 0x04

//! Reserved Feature Bits
/*
    Described in 6th section
*/
/* If this feature has been negotiated by driver, the device MUST issue a used buffer notification if the device runs out of available descriptors on a virtqueue, even though notifications are suppressed using the VIRTQ_AVAIL_F_NO_INTERRUPT flag or the used_event field.  */
#define VIRTIO_F_NOTIFY_ON_EMPTY (1 << 24)
/* This feature indicates that the device accepts arbitrary descriptor layouts, as described in Section 2.6.4.3 Legacy Interface: Message Framing.  */
#define VIRTIO_F_ANY_LAYOUT (1 << 27)
/*  Negotiating this feature indicates that the driver can use descriptors
    with the VIRTQ_DESC_F_INDIRECT flag set, as described in 2.6.5.3
    Indirect Descriptors and 2.7.7 Indirect Flag : Scatter - Gather Support. */
#define VIRTIO_F_RING_INDIRECT_DESC (1 << 28)
/* This feature enables the used_event and the avail_event fields as described in 2.6.7, 2.6.8 and 2.7.10. */
#define VIRTIO_F_RING_EVENT_IDX (1 << 29)
/* This indicates compliance with this specification, giving a simple way to detect legacy devices or drivers.  */
#define VIRTIO_F_VERSION_1 (1 << 32)
/* This feature indicates that the device can be used on a platform where device access to data in memory is limited and/or translated */
#define VIRTIO_F_ACCESS_PLATFORM (1 << 33)
/* This feature indicates support for the packed virtqueue layout as described in 2.7 Packed Virtqueues.  */
#define VIRTIO_F_RING_PACKED (1 << 34)
/* This feature indicates that all buffers are used by the device in the same order in which they have been made available.  */
#define VIRTIO_F_IN_ORDER (1 << 35)
/* This feature indicates that memory accesses by the driver and the device are ordered in a way described by the platform.  */
#define VIRTIO_F_ORDER_PLATFORM (1 << 36)
/* This feature indicates that the device supports Single Root I/O Virtualization. Currently only PCI devices support this feature.  */
#define VIRTIO_F_SR_IOV (1 << 37)
/* This feature indicates that the driver passes extra data (besides identifying the virtqueue) in its device notifications. See 2.7.23 Driver notifications. */
#define VIRTIO_F_NOTIFICATION_DATA (1 << 38)

//! Virtio Structure PCI Capabilities
/*
    Described in 4.1.4
*/
/* Common configuration */
#define VIRTIO_PCI_CAP_COMMON_CFG 0x01
/* Notifications */
#define VIRTIO_PCI_CAP_NOTIFY_CFG 0x02
/* ISR Status */
#define VIRTIO_PCI_CAP_ISR_CFG 0x03
/* Device specific configuration */
#define VIRTIO_PCI_CAP_DEVICE_CFG 0x04
/* PCI configuration access */
#define VIRTIO_PCI_CAP_PCI_CFG 0x05

//! Virtqueue Descriptor Flags
/* 2.7.6 Next Flag: Descriptor Chaining */
/* This marks a buffer as continuing via the next field. */
#define VIRTQ_DESC_F_NEXT 0x01
/* 2.7.3 Write Flag */
/* This marks a buffer as device write-only (otherwise device read-only). */
#define VIRTQ_DESC_F_WRITE 0x02
/* 2.7.7 Indirect Flag: Scatter-Gather Support */
/* This means the buffer contains a list of buffer descriptors. */
#define VIRTQ_DESC_F_INDIRECT 0x04

/* The driver uses this in driver-area->flags to advise the device:
   don’t interrupt me when you consume a buffer.
   It’s unreliable, so it’s simply an optimization.  */
#define VIRTQ_AVAIL_F_NO_INTERRUPT 0x1

/* The device uses this in device-area->flags to advise the driver:
   don’t kick me when you add a buffer.
   It’s unreliable, so it’s simply an optimization. */
#define VIRTQ_USED_F_NO_NOTIFY 0x01

/*
    4.1.4 Virtio Structure PCI Capabilities
*/
typedef struct virtio_pci_cap
{
    uint8_t cap_vndr;   /* Generic PCI field: PCI_CAP_ID_VNDR */
    uint8_t cap_next;   /* Generic PCI field: next ptr. */
    uint8_t cap_len;    /* Generic PCI field: capability length */
    uint8_t cfg_type;   /* Identifies the structure. */
    uint8_t bar;        /* Where to find it. */
    uint8_t padding[3]; /* Pad to full dword. */
    uint32_t offset;    /* Offset within bar. */
    uint32_t length;    /* Length of the structure, in bytes. */
} virtio_pci_cap;

/*
    4.1.4.3 Common configuration structure layout
*/
typedef struct virtio_pci_common_cfg
{
    /* About the whole device. */
    uint32_t device_feature_select; /* read-write */
    uint32_t device_feature;        /* read-only for driver */
    uint32_t driver_feature_select; /* read-write */
    uint32_t driver_feature;        /* read-write */
    uint16_t msix_config;           /* read-write */
    uint16_t num_queues;            /* read-only for driver */
    uint8_t device_status;          /* read-write */
    uint8_t config_generation;      /* read-only for driver */

    /* About a specific virtqueue. */
    uint16_t queue_select;      /* read-write */
    uint16_t queue_size;        /* read-write */
    uint16_t queue_msix_vector; /* read-write */
    uint16_t queue_enable;      /* read-write */
    uint16_t queue_notify_off;  /* read-only for driver */
    uint64_t queue_desc;        /* read-write */
    uint64_t queue_driver;      /* read-write */
    uint64_t queue_device;      /* read-write */
} virtio_pci_common_cfg;

/*
    4.1.4.4 Notification structure layout
*/
typedef struct virtio_pci_notify_cap
{
    struct virtio_pci_cap cap;
    uint32_t notify_off_multiplier; /* Multiplier for queue_notify_off. */
} virtio_pci_notify_cap;

/*
    2.6.5 The Virtqueue Descriptor Table
*/
typedef struct virtq_descriptor
{
    /* Address (guest-physical). */
    uint64_t address;
    uint32_t length;
    /* The flags, see: Virtqueue Descriptor Flags */
    uint16_t flags;
    /* Next field if flags & NEXT */
    uint16_t next;
} virtq_descriptor;

/*
    2.6.6 The Virtqueue Available Ring
*/
typedef struct virtq_driver_area
{
    uint16_t flags;
    /*
        Index field indicates where the driver would put the next descriptor entry in the ring (modulo the queue size).
        This starts at 0, and increases.
    */
    uint16_t index;
    /* ring_buffer is queue-size elements long.
    Entries refers to the head of a descriptor chain. (2 * queue-size)*/
    uint16_t ring_buffer[1];
    // uint16_t used_event (Only available when VIRTIO_F_EVENT_IDX is negotiated)
} virtq_driver_area;

/*
    2.6.8 The Virtqueue Used Ring
*/
typedef struct virtq_device_element
{
    /* Index of start of used descriptor chain. */
    uint32_t index;
    /* Total length of the descriptor chain which was used (written to) */
    uint32_t length;
} virtq_device_element;

/*
    2.6.8 The Virtqueue Used Ring
*/
typedef struct virtq_device_area
{
    uint16_t flags;
    /*
        Index field indicates where the device would put
        the next descriptor entry in the ring (modulo the queue size).
        This starts at 0, and increases
    */
    uint16_t index;
    /* Each element describes a used descriptor, including the index and length. (4 * queue-size) */
    virtq_device_element ring_buffer[1];
} virtq_device_area;

/*
    2.5 Virtqueues
*/
typedef struct virtq
{
    uint16_t size;                     //  queue size
    virtq_descriptor *descriptor_area; //  array of descriptors (length determined by previous field)
    virtq_driver_area *driver_area;    //  data supplied by the driver to the device (available ring)
    virtq_device_area *device_area;    //  data supplied by the device to the driver (used ring)
    uint16_t next_descriptor;          //  index of the next slot in the descriptor area that should be used
    uint16_t last_device_index;        /*  the last known value of device_area->index
                                           If value doesn't equal device_area->index,
                                           the device has added used descriptors to
                                           device_area->ring_buffer.*/
} virtq;

//! virtio_setup_queue
/*
    @virtqueue pointer to virtque - memory for structure should be allocated before
    @size - size of virtqueue
    If fails - returns non-zero
*/
uint8_t virtio_setup_queue(virtq *virtqueue, uint16_t size);

#endif