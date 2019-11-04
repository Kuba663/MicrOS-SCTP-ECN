#ifndef HARDDISK_H
#define HARDDISK_H

#include <stdint.h>
#include <stdbool.h>
#include "harddisk_pio_mode_header.h"
#include "harddisk_identify_devide_data.h"
#include "assembly/io.h"

//! Enum represent bus type.
typedef enum BUS_TYPE
{
    HARDDISK_PRIMARY_BUS = 1, /*!< Primary bus. */
    HARDDISK_SECONDARY_BUS = 2 /*!< Secondary bus. */
} BUS_TYPE;

//! Enum represent hard disk type.
typedef enum MASTER_SLAVE
{
    HARDDISK_MASTER = 1, /*!< Master hard disk. */
    HARDDISK_SLAVE = 0 /*!< Slave hard disk. */
} MASTER_SLAVE;

//! Enum represent hard disk status.
typedef enum HARDDISK_STATE
{
    HARDDISK_PRESENT = 1, /*!< Present. */
    HARDDISK_NOT_PRESENT = 0, /*!< Not present. */
    HARDDISK_ERROR = -1 /*!< Error. */
} HARDDISK_STATE;

//! Defines status of hard disks in system.
typedef struct harddisk_states
{
    //! Presence of primary master
    HARDDISK_STATE primary_master;
    //! Data of primary master
    harddisk_identify_device_data primary_master_data;
    //! Presence of primary slave
    HARDDISK_STATE primary_slave;
    //! Data of primary slave
    harddisk_identify_device_data primary_slave_data;
    //! Presence of secondary master
    HARDDISK_STATE secondary_master;
    //! Data of secondary master
    harddisk_identify_device_data secondary_master_data;
    //! Presence of secondary slave
    HARDDISK_STATE secondary_slave;
    //! Data of secondary slave
    harddisk_identify_device_data secondary_slave_data;
} harddisk_states;

//! Initialization of hard disk driver.
/*!
    Should be called during boot up once. Check for hard disks and store informations about them.
*/
void harddisk_init();

//! Get hard disk states.
/*!
    Call this function after init, which should be called during system boot up.
    \return State off all hard drives in system.
*/
harddisk_states get_harddisk_states();

//! Check hard disk presence in computer.
/*!
    Check if given hard disk is installed in computer.
    \param master Set 1 to check master, set 2 to check slave.
    \param bus Set 1 to check primary bus, set 2 to check secondary bus.
    \return 0 no disk, 1 disk present, -1 disk present but ERR set, -2 wrong parameters.
*/
uint8_t check_harddisk_presence(MASTER_SLAVE master, BUS_TYPE bus);

#endif