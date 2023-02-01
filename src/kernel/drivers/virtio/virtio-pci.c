#include "virtio-pci.h"

// TODO: Error-checking
uint8_t virtio_setup_queue(virtq *virtqueue, uint16_t queueSize)
{
    // Zero virtqueue structure
    memset(virtqueue, 0, sizeof(virtq));

    uint32_t descriptorTableSize = 16 * queueSize;

    // driver area (AKA available ring) must be aligned on a 2-byte boundary, which it always will be because descriptorSize will be aligned to
    // a 4096-byte boundary and its size will be a multiple of 16.
    uint32_t driverAreaSize = 2 * queueSize + 6;

    // device area (AKA used ring) must be aligned on a 4096-byte boundary (because this is a legacy driver), which it probably won't be
    uint32_t driverAreaPadding = 0;
    if ((driverAreaSize + descriptorTableSize) % 4096 != 0)
        driverAreaPadding = 4096 - ((driverAreaSize + descriptorTableSize) % 4096);

    uint32_t deviceAreaSize = 8 * queueSize + 6;

    uint32_t virtqueueByteSize = descriptorTableSize + driverAreaSize + driverAreaPadding + deviceAreaSize;

    // Allocate memory for virtqueue + extra bytes for 4096-byte alignment
    uint32_t *virtqueue_mem = (uint32_t *)heap_kernel_alloc(virtqueueByteSize, 4096);

    // Zero virtqueue memory
    memset(virtqueue_mem, 0, virtqueueByteSize);

    // Get a 4096-byte aligned block of memory
    // virtq *virtqueue = virtqueue_mem;
    if ((uint32_t)virtqueue_mem % 4096)
        virtqueue_mem = (uint32_t *)((uint32_t)virtqueue_mem + 4096 - (uint32_t)virtqueue_mem % 4096);

    // setup elements of virtqueue
    virtqueue->size = queueSize;
    // descriptors will point to the first byte of virtqueue_mem
    virtqueue->descriptor_area = (virtq_descriptor *)virtqueue_mem;
    // driverArea  will follow descriptors
    virtqueue->driver_area = (virtq_driver_area *)((uint32_t)virtqueue_mem + descriptorTableSize);
    // deviceArea will follow driver area + padding bytes
    virtqueue->device_area = (virtq_device_area *)((uint32_t)virtqueue->driver_area + driverAreaSize + driverAreaPadding);

    return 0;
}
