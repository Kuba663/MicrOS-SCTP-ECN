#include "mode_13h.h"
#include "drivers/vga/modes/registerfunctions.h"
#include "memory/heap/heap.h"
#include "drivers/dal/videocard/videocard.h"



//REGISTER VALUES
uint8_t g_320x200x256[] =
	{
	/* MISC */
		0x63, 
	/* SEQ */
		0x03, 0x01, 0x0F, 0x00, 0x0E, 
	/* CRTC */
		0x5F, 0x4F, 0x50, 0x82, 0x54, 0x80, 0xBF, 0x1F,
		0x00, 0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x8E, 0x8F, 0x28, 0x40, 0x96, 0xB9, 0xA3,
		0xFF, 
	/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x05, 0x0F,
		0xFF, 
	/* AC */
		0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
		0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
		0x41, 0x00, 0x0F, 0x00, 0x00, 
	};

//PALETTE
unsigned char palette13H[] = {
	0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
    0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x00, 0x05, 0x05, 0x05, 0x08, 0x08, 0x08, 0x0B, 0x0B, 0x0B, 0x0E, 0x0E, 0x0E, 0x11, 
    0x11, 0x11, 0x14, 0x14, 0x14, 0x18, 0x18, 0x18, 0x1C, 0x1C, 0x1C, 0x20, 0x20, 0x20, 0x24, 0x24, 
    0x24, 0x28, 0x28, 0x28, 0x2D, 0x2D, 0x2D, 0x32, 0x32, 0x32, 0x38, 0x38, 0x38, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x3F, 0x10, 0x00, 0x3F, 0x1F, 0x00, 0x3F, 0x2F, 0x00, 0x3F, 0x3F, 0x00, 0x3F, 0x3F, 
    0x00, 0x2F, 0x3F, 0x00, 0x1F, 0x3F, 0x00, 0x10, 0x3F, 0x00, 0x00, 0x3F, 0x10, 0x00, 0x3F, 0x1F, 
    0x00, 0x3F, 0x2F, 0x00, 0x3F, 0x3F, 0x00, 0x2F, 0x3F, 0x00, 0x1F, 0x3F, 0x00, 0x10, 0x3F, 0x00, 
    0x00, 0x3F, 0x00, 0x00, 0x3F, 0x10, 0x00, 0x3F, 0x1F, 0x00, 0x3F, 0x2F, 0x00, 0x3F, 0x3F, 0x00, 
    0x2F, 0x3F, 0x00, 0x1F, 0x3F, 0x00, 0x10, 0x3F, 0x1F, 0x1F, 0x3F, 0x27, 0x1F, 0x3F, 0x2F, 0x1F, 
    0x3F, 0x37, 0x1F, 0x3F, 0x3F, 0x1F, 0x3F, 0x3F, 0x1F, 0x37, 0x3F, 0x1F, 0x2F, 0x3F, 0x1F, 0x27, 
    0x3F, 0x1F, 0x1F, 0x3F, 0x27, 0x1F, 0x3F, 0x2F, 0x1F, 0x3F, 0x37, 0x1F, 0x3F, 0x3F, 0x1F, 0x37, 
    0x3F, 0x1F, 0x2F, 0x3F, 0x1F, 0x27, 0x3F, 0x1F, 0x1F, 0x3F, 0x1F, 0x1F, 0x3F, 0x27, 0x1F, 0x3F, 
    0x2F, 0x1F, 0x3F, 0x37, 0x1F, 0x3F, 0x3F, 0x1F, 0x37, 0x3F, 0x1F, 0x2F, 0x3F, 0x1F, 0x27, 0x3F, 
    0x2D, 0x2D, 0x3F, 0x31, 0x2D, 0x3F, 0x36, 0x2D, 0x3F, 0x3A, 0x2D, 0x3F, 0x3F, 0x2D, 0x3F, 0x3F, 
    0x2D, 0x3A, 0x3F, 0x2D, 0x36, 0x3F, 0x2D, 0x31, 0x3F, 0x2D, 0x2D, 0x3F, 0x31, 0x2D, 0x3F, 0x36, 
    0x2D, 0x3F, 0x3A, 0x2D, 0x3F, 0x3F, 0x2D, 0x3A, 0x3F, 0x2D, 0x36, 0x3F, 0x2D, 0x31, 0x3F, 0x2D, 
    0x2D, 0x3F, 0x2D, 0x2D, 0x3F, 0x31, 0x2D, 0x3F, 0x36, 0x2D, 0x3F, 0x3A, 0x2D, 0x3F, 0x3F, 0x2D, 
    0x3A, 0x3F, 0x2D, 0x36, 0x3F, 0x2D, 0x31, 0x3F, 0x00, 0x00, 0x1C, 0x07, 0x00, 0x1C, 0x0E, 0x00, 
    0x1C, 0x15, 0x00, 0x1C, 0x1C, 0x00, 0x1C, 0x1C, 0x00, 0x15, 0x1C, 0x00, 0x0E, 0x1C, 0x00, 0x07, 
    0x1C, 0x00, 0x00, 0x1C, 0x07, 0x00, 0x1C, 0x0E, 0x00, 0x1C, 0x15, 0x00, 0x1C, 0x1C, 0x00, 0x15, 
    0x1C, 0x00, 0x0E, 0x1C, 0x00, 0x07, 0x1C, 0x00, 0x00, 0x1C, 0x00, 0x00, 0x1C, 0x07, 0x00, 0x1C, 
    0x0E, 0x00, 0x1C, 0x15, 0x00, 0x1C, 0x1C, 0x00, 0x15, 0x1C, 0x00, 0x0E, 0x1C, 0x00, 0x07, 0x1C, 
    0x0E, 0x0E, 0x1C, 0x11, 0x0E, 0x1C, 0x15, 0x0E, 0x1C, 0x18, 0x0E, 0x1C, 0x1C, 0x0E, 0x1C, 0x1C, 
    0x0E, 0x18, 0x1C, 0x0E, 0x15, 0x1C, 0x0E, 0x11, 0x1C, 0x0E, 0x0E, 0x1C, 0x11, 0x0E, 0x1C, 0x15, 
    0x0E, 0x1C, 0x18, 0x0E, 0x1C, 0x1C, 0x0E, 0x18, 0x1C, 0x0E, 0x15, 0x1C, 0x0E, 0x11, 0x1C, 0x0E, 
    0x0E, 0x1C, 0x0E, 0x0E, 0x1C, 0x11, 0x0E, 0x1C, 0x15, 0x0E, 0x1C, 0x18, 0x0E, 0x1C, 0x1C, 0x0E, 
    0x18, 0x1C, 0x0E, 0x15, 0x1C, 0x0E, 0x11, 0x1C, 0x14, 0x14, 0x1C, 0x16, 0x14, 0x1C, 0x18, 0x14, 
    0x1C, 0x1A, 0x14, 0x1C, 0x1C, 0x14, 0x1C, 0x1C, 0x14, 0x1A, 0x1C, 0x14, 0x18, 0x1C, 0x14, 0x16, 
    0x1C, 0x14, 0x14, 0x1C, 0x16, 0x14, 0x1C, 0x18, 0x14, 0x1C, 0x1A, 0x14, 0x1C, 0x1C, 0x14, 0x1A, 
    0x1C, 0x14, 0x18, 0x1C, 0x14, 0x16, 0x1C, 0x14, 0x14, 0x1C, 0x14, 0x14, 0x1C, 0x16, 0x14, 0x1C, 
    0x18, 0x14, 0x1C, 0x1A, 0x14, 0x1C, 0x1C, 0x14, 0x1A, 0x1C, 0x14, 0x18, 0x1C, 0x14, 0x16, 0x1C, 
    0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 0x00, 0x10, 0x0C, 0x00, 0x10, 0x10, 0x00, 0x10, 0x10, 
    0x00, 0x0C, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04, 0x10, 0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 
    0x00, 0x10, 0x0C, 0x00, 0x10, 0x10, 0x00, 0x0C, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04, 0x10, 0x00, 
    0x00, 0x10, 0x00, 0x00, 0x10, 0x04, 0x00, 0x10, 0x08, 0x00, 0x10, 0x0C, 0x00, 0x10, 0x10, 0x00, 
    0x0C, 0x10, 0x00, 0x08, 0x10, 0x00, 0x04, 0x10, 0x08, 0x08, 0x10, 0x0A, 0x08, 0x10, 0x0C, 0x08, 
    0x10, 0x0E, 0x08, 0x10, 0x10, 0x08, 0x10, 0x10, 0x08, 0x0E, 0x10, 0x08, 0x0C, 0x10, 0x08, 0x0A, 
    0x10, 0x08, 0x08, 0x10, 0x0A, 0x08, 0x10, 0x0C, 0x08, 0x10, 0x0E, 0x08, 0x10, 0x10, 0x08, 0x0E, 
    0x10, 0x08, 0x0C, 0x10, 0x08, 0x0A, 0x10, 0x08, 0x08, 0x10, 0x08, 0x08, 0x10, 0x0A, 0x08, 0x10, 
    0x0C, 0x08, 0x10, 0x0E, 0x08, 0x10, 0x10, 0x08, 0x0E, 0x10, 0x08, 0x0C, 0x10, 0x08, 0x0A, 0x10, 
    0x0B, 0x0B, 0x10, 0x0C, 0x0B, 0x10, 0x0D, 0x0B, 0x10, 0x0F, 0x0B, 0x10, 0x10, 0x0B, 0x10, 0x10, 
    0x0B, 0x0F, 0x10, 0x0B, 0x0D, 0x10, 0x0B, 0x0C, 0x10, 0x0B, 0x0B, 0x10, 0x0C, 0x0B, 0x10, 0x0D, 
    0x0B, 0x10, 0x0F, 0x0B, 0x10, 0x10, 0x0B, 0x0F, 0x10, 0x0B, 0x0D, 0x10, 0x0B, 0x0C, 0x10, 0x0B, 
    0x0B, 0x10, 0x0B, 0x0B, 0x10, 0x0C, 0x0B, 0x10, 0x0D, 0x0B, 0x10, 0x0F, 0x0B, 0x10, 0x10, 0x0B, 
    0x0F, 0x10, 0x0B, 0x0D, 0x10, 0x0B, 0x0C, 0x10, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//DOUBLE BUFFER POINTER;

unsigned char *mode13h_buffer = NULL;

int8_t mode13h_set_mode()
{
    writeRegisters(g_320x200x256);
    set_vga_palette(palette13H);
    mode13h_clear_screen();
    video_card_set_turn_on_buffer_func(&mode13h_turn_on_buffer);
    video_card_set_turn_off_buffer_func(&mode13h_turn_off_buffer);
    video_card_set_is_buffer_on_func(&mode13h_is_buffer_on);
    video_card_set_swap_buffers_func(&mode13h_swap_buffers);
    video_card_set_draw_pixel_func(&mode13h_draw_pixel);
    video_card_set_draw_line_func(&mode13h_draw_line);
    video_card_set_draw_circle_func(&mode13h_draw_circle);
    video_card_set_draw_rectangle_func(&mode13h_draw_rectangle);
    video_card_set_clear_screen_func(&mode13h_clear_screen);

    video_card_set_print_char_func(NULL);
	video_card_set_print_char_color_func(NULL);
	video_card_set_print_string_func(NULL);
	video_card_set_print_string_color_func(NULL);
	video_card_set_set_char_func(NULL);
	video_card_set_get_char_func(NULL);
	video_card_set_set_color_func(NULL);
	video_card_set_get_color_func(NULL);
	video_card_set_set_char_and_color_func(NULL);
	video_card_set_get_char_and_color_func(NULL);
	video_card_set_set_cursor_pos_func(NULL);
	video_card_set_get_cursor_pos_func(NULL);
	video_card_set_turn_cursor_on_func(NULL);
	video_card_set_turn_cursor_off_func(NULL);

    video_card_set_print_char_external_buffer(NULL);
	video_card_set_print_char_color_external_buffer(NULL);
	video_card_set_print_string_external_buffer(NULL);
	video_card_set_print_string_color_external_buffer(NULL);
	video_card_set_set_char_external_buffer(NULL);
	video_card_set_get_char_external_buffer(NULL);
	video_card_set_set_color_external_buffer(NULL);
	video_card_set_get_color_external_buffer(NULL);
	video_card_set_set_char_and_color_external_buffer(NULL);
	video_card_set_get_char_and_color_external_buffer(NULL);
    return 0x13;
}

int8_t mode13h_turn_on_buffer()
{
    if(mode13h_buffer != NULL) return -1;
    mode13h_buffer = heap_kernel_alloc(MODE13H_HEIGHT * MODE13H_WIDTH, 0);
    if(mode13h_buffer == NULL)
        return -1;
    video_card_set_draw_pixel_func(&mode13h_draw_pixel_buffered);
    video_card_set_draw_line_func(&mode13h_draw_line_buffered);
    video_card_set_draw_circle_func(&mode13h_draw_circle_buffered);
    video_card_set_draw_rectangle_func(&mode13h_draw_rectangle_buffered);
    video_card_set_clear_screen_func(&mode13h_clear_screen_buffered);
    return 0;
}

int8_t mode13h_turn_off_buffer()
{
    if(mode13h_buffer == NULL) return -1;
    heap_kernel_dealloc(mode13h_buffer);
    mode13h_buffer = NULL;
    video_card_set_draw_pixel_func(&mode13h_draw_pixel);
    video_card_set_draw_line_func(&mode13h_draw_line);
    video_card_set_draw_circle_func(&mode13h_draw_circle);
    video_card_set_draw_rectangle_func(&mode13h_draw_rectangle);
    video_card_set_clear_screen_func(&mode13h_clear_screen);
    return 0;
}

uint8_t mode13h_is_buffer_on()
{
    return mode13h_buffer != NULL;
}

int8_t mode13h_swap_buffers()
{
    if(mode13h_buffer == NULL) return -1;
    memcpy(VGA_VRAM, mode13h_buffer, MODE13H_HEIGHT * MODE13H_WIDTH);
    return 0;
}

int8_t mode13h_draw_pixel(uint8_t color, uint16_t x, uint16_t y)
{
    if((x>=MODE13H_WIDTH) || (y >=MODE13H_HEIGHT))
        return -1;
    unsigned char *fb = (unsigned char *) VGA_VRAM;
    fb[y * MODE13H_WIDTH + x] = color;
    return 0;
}

int8_t mode13h_draw_line(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode13h_draw_pixel(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode13h_draw_pixel(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode13h_draw_pixel(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode13h_draw_pixel(color, a * y + b, y);
    }
    return 0;
}

int8_t mode13h_draw_circle(uint8_t color, uint16_t x, uint16_t y, uint16_t radius) 
{
    return 0;
}

int8_t mode13h_draw_rectangle(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode13h_clear_screen()
{
    memset(VGA_VRAM, 0, 256 * 1024);
    return 0;
}

int8_t mode13h_draw_pixel_buffered(uint8_t color, uint16_t x, uint16_t y)
{
    if((mode13h_buffer == NULL) || (x>=MODE13H_WIDTH) || (y >=MODE13H_HEIGHT))
        return -1;
    mode13h_buffer[y * MODE13H_WIDTH + x] = color;
    return 0;
}

int8_t mode13h_draw_line_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    if(mode13h_buffer == NULL) return -1;
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode13h_draw_pixel_buffered(color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode13h_draw_pixel_buffered(color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode13h_draw_pixel_buffered(color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode13h_draw_pixel_buffered(color, a * y + b, y);
    }
    return 0;
}
int8_t mode13h_draw_circle_buffered(uint8_t color, uint16_t x, uint16_t y, uint16_t radius)
{
    return 0;
}
int8_t mode13h_draw_rectangle_buffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t mode13h_clear_screen_buffered()
{
    if(mode13h_buffer == NULL) return -1;
    memset(mode13h_buffer, 0, 256 * 1024);
    return 0;
}

int8_t mode13h_draw_pixel_external_buffer(uint8_t* buffer, uint16_t mode, int8_t color, uint16_t x, uint16_t y){
    if((x>=MODE13H_WIDTH) || (y >=MODE13H_HEIGHT)){
        return -1;
    }
	buffer[y * MODE13H_WIDTH + x] = color;
    return 0;
}
int8_t mode13h_draw_line_external_buffer(uint8_t* buffer, uint16_t mode, uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by){
    if(ax == bx) return -1;
    int32_t dx = (int32_t)bx - ax;
    int32_t dy = (int32_t)by - ay;
    if(_abs(dx) >= _abs(dy))
    {
        float a = dy/(float)(dx);
        float b = ay - a * ax;
        if(ax > bx)
            for(int x = bx; x <= ax; ++x)
                mode13h_draw_pixel_external_buffer(buffer, mode, color, x, a * x + b);
        else
            for(int x = ax; x <= bx; ++x)
                mode13h_draw_pixel_external_buffer(buffer, mode, color, x, a * x + b);
    }
    else
    {
        float a = dx/(float)(dy);
        float b = ax - a * ay;
        if(ay > by)
            for(int y = by; y <= ay; ++ y)
                mode13h_draw_pixel_external_buffer(buffer, mode, color, a * y + b, y);
        else
            for(int y = ay; y <= by; ++ y)
                mode13h_draw_pixel_external_buffer(buffer, mode, color, a * y + b, y);
    }
    return 0;
}
int8_t mode13h_draw_circle_external_buffer(uint8_t* buffer, uint16_t mode, uint8_t color, uint16_t x, uint16_t y, uint16_t radius){
    return -1;
}
int8_t mode13h_draw_rectangle_external_buffer(uint8_t* buffer, uint16_t mode, uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by){
    return -1;
}
int8_t mode13h_clear_screen_external_buffer(uint8_t* buffer, uint16_t mode)
{
    memset(buffer, 0, MODE13H_WIDTH * MODE13H_HEIGHT);
    return 0;
}

int8_t mode13h_swap_external_buffer(uint8_t* buffer, uint16_t mode)
{
    memcpy(VGA_VRAM, buffer, MODE13H_WIDTH * MODE13H_HEIGHT);
    return 0;
}
uint8_t* mode13h_create_external_buffer(uint16_t mode)
{
    uint8_t* ptr = heap_kernel_alloc(MODE13H_HEIGHT * MODE13H_WIDTH, 0);
    memset(ptr, 0, MODE13H_HEIGHT * MODE13H_WIDTH);
    return ptr;
}