#include "mouse.h"

uint8_t cycle = 0, mouse_data[3];
    
void ps2mouse_init()
{
    pic_enable_irq(IRQ_NUM);                                     // IRQ Controller
    idt_attach_interrupt_handler(IRQ_NUM, ps2mouse_irq_handler); // CPU IDT

    // Check if PS/2 controller is available to write
    while (ps2mouse_check_buffer_status(Input) != Empty)
    {
        io_out_byte(0x64, 0xA8); // Enable PS/2 second port
    }

    uint8_t configurationByte = 0;

    // reading the configuration byte
    if (ps2mouse_check_buffer_status(Input) == Empty)
    {
        io_out_byte(0x64, 0x20);
    }
    if (ps2mouse_check_buffer_status(Output) == Full)
    {
        configurationByte = io_in_byte(0x60);
    }

    // editing
    configurationByte |= 0x02;

    // writing
    if (ps2mouse_check_buffer_status(Input) == Empty)
    {
        io_out_byte(0x64, 0x60);
    }
    if (ps2mouse_check_buffer_status(Input) == Empty)
    {
        io_out_byte(0x60, configurationByte);
    }

    // Set defaults
    ps2mouse_write(0xF6);
    // Ack, passing dummy pointer
    if (!ps2mouse_read(&configurationByte))
    {
        return;
    }

    // Enable data reporting
    ps2mouse_write(0xF4);
    //Ack, passing dummy pointer
    if (!ps2mouse_read(&configurationByte))
    {
        return;
    }
}

bool ps2mouse_irq_handler()
{
    logger_log_info("** Odglosy myszy **");

    switch (cycle)
    {
    case 0:
        mouse_data[0] = inportb(0x60);
        cycle++;
        break;
    case 1:
        mouse_data[1] = inportb(0x60);
        cycle++;
        break;
    case 2:
        mouse_data[2] = inportb(0x60);
        cycle = 0;
        break;
    }

    return false;
}

BufferStatus ps2mouse_check_buffer_status(BufferType type)
{
    uint32_t i = TIMEOUT;
    switch (type)
    {
    case Input:

        while (i)
        {
            if ((io_in_byte(0x64) & 0x02) == 0)
            {
                return Empty;
            }
            i--;
        }
        return Full;

    case Output:

        while (i)
        {
            if ((io_in_byte(0x64) & 0x01) == 1)
            {
                return Full;
            }
            i--;
        }
        return Empty;
    };
}

bool ps2mouse_write(uint8_t byte)
{
    if (ps2mouse_check_buffer_status(Input) != Empty)
    {
        return false;
    }

    io_out_byte(0x64, 0xD4);

    if (ps2mouse_check_buffer_status(Input) != Empty)
    {
        return false;
    }

    io_out_byte(0x60, byte);

    return true;
}

bool ps2mouse_read(uint8_t *byte)
{
    if (byte == NULL)
    {
        return false;
    }
    if (ps2mouse_check_buffer_status(Output) != Full)
    {
        return false;
    }

    *byte = io_in_byte(0x60);

    return true;
}

void ps2mouse_get_cursor_position()
{
}

void ps2mouse_set_cursor_position()
{
}