#include "harddisk_header.h"

//! Current states of all hard drives.
harddisk_states harddisk_current_states;
//! Current configuration of harddisk
harddisk_configuration harddisk_current_configuration;

int8_t __harddisk_soft_reset_port(uint16_t control_port)
{
    // Set SRST bit
    harddisk_control_device_control_register message = {.value = 0};
    message.fields.software_reset = 1;
    io_out_byte(control_port, message.value);
    // We should wait at least 5 μs, but now MicrOS can't count μs
    uint32_t start_time = timer_get_system_clock();
    uint32_t stop_time = 0;
    for(;;)
    {
        stop_time = timer_get_system_clock();
        if(stop_time - start_time >= 2)
        {
            break;
        }
    }

    message.fields.software_reset = 0;
    io_out_byte(control_port, message.value);

    // Wait 2 ms
    start_time = timer_get_system_clock();
    for(;;)
    {
        stop_time = timer_get_system_clock();
        if(stop_time - start_time >= 2)
        {
            break;
        }
    }

    // Pull BSY until clears
    return __harddisk_bsy_poll(control_port);
}


void __harddisk_400ns_delay(uint16_t control_port)
{
    if(harddisk_current_configuration.delay_by_reading_port)
    {
        for(int i = 0; i < 15; ++i)
        {
            io_in_byte(control_port);
        }
    }
    else
    {
        uint32_t start_time = timer_get_system_clock();
        uint32_t stop_time = 0;
        for(;;)
        {
            stop_time = timer_get_system_clock();
            if(stop_time - start_time >= 1)
            {
                break;
            }
        }
    } 
}

int8_t __harddisk_bsy_poll(uint16_t control_port)
{
    harddisk_io_control_status_register result;
    uint32_t start_time = timer_get_system_clock();
    uint32_t stop_time = 0;
    for(;;)
    {
        result.value = io_in_byte(control_port);
        if(result.fields.busy == 0)
        {
            return 1;
        }
        stop_time = timer_get_system_clock();
        if(stop_time - start_time >= HARDDISK_BSY_ERROR_DELAY)
        {
            return -1;
        }
    }
}


void __harddisk_get_pointers(HARDDISK_ATA_MASTER_SLAVE type, HARDDISK_ATA_BUS_TYPE bus, const HARDDISK_STATE **state, const harddisk_identify_device_data **data)
{
    *state = NULL;
    *data = NULL;
    switch(type)
    {
    case HARDDISK_ATA_MASTER:
        switch(bus)
        {
            case HARDDISK_ATA_PRIMARY_BUS:
                // Primary master
                *state = &harddisk_current_states.primary_master;
                *data = &harddisk_current_states.primary_master_data;
                break;
            case HARDDISK_ATA_SECONDARY_BUS:
                // Secondary master
                *state = &harddisk_current_states.secondary_master;
                *data = &harddisk_current_states.secondary_master_data;
                break;
            default:
                return;
        }
        break;
    case HARDDISK_ATA_SLAVE:
        switch(bus)
        {
            case HARDDISK_ATA_PRIMARY_BUS:
                // Primary slave
                *state = &harddisk_current_states.primary_slave;
                *data = &harddisk_current_states.primary_slave_data;
                break;
            case HARDDISK_ATA_SECONDARY_BUS:
                // Secondary slave
                *state = &harddisk_current_states.secondary_slave;
                *data = &harddisk_current_states.secondary_slave_data;
                break;
            default:
                return;
        }
        break;
    default:
        return;      
    }
}