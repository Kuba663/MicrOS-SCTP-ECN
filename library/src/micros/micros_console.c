#include "micros_console.h"

micros_console_color foreground_color = micros_console_color_light_gray;
micros_console_color background_color = micros_console_color_black;

void micros_console_print_char(char c)
{
    micros_interrupt_3a(0x0100, (uint32_t)c, (uint32_t)foreground_color, (uint32_t)background_color);
}

void micros_console_print_string(const char *str)
{
    micros_interrupt_3a(0x0101, (uint32_t)str, (uint32_t)foreground_color, (uint32_t)background_color);
}

char micros_console_get_char_at_position(micros_console_position *position)
{
    return (char)micros_interrupt_2a(0x0102, position->x, position->y);
}

void micros_console_set_foreground_color(micros_console_color color)
{
    foreground_color = color;
}

void micros_console_set_background_color(micros_console_color color)
{
    background_color = color;
}

void micros_console_set_cursor_position(micros_console_position *position)
{
    micros_interrupt_2a(0x0103, position->x, position->y);
}

void micros_console_get_cursor_position(micros_console_position *position)
{
    micros_interrupt_1a(0x0104, (uint32_t)position);
}

void micros_console_clear()
{
    micros_interrupt_0a(0x0105);
}

void micros_console_set_cursor_visibility(bool visibility)
{
    micros_interrupt_1a(0x0106, (uint32_t)visibility);
}

void micros_console_set_video_mode(uint8_t mode)
{
    micros_interrupt_1a(0x010B, mode);
}

void micros_console_copy_from_buffer(uint8_t* buffer, uint32_t how_many)
{
    micros_interrupt_2a(0x010C, (uint32_t)buffer, how_many);
}