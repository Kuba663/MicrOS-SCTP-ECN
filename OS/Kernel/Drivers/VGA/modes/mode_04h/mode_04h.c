#include "mode_04H.h"
#include "../registerFunctions.h"
#include "../../../../Memory/Manager/Heap/heap.h"
#include "../../../DAL/VideoCard/videocard.h"

//REGISTER VALUES
unsigned char g_320x200x4c[] =
	{
	/* MISC */
		0x63, 
	/* SEQ */
		0x03, 0x09, 0x03, 0x00, 0x02, 
	/* CRTC */
		0x2D, 0x27, 0x28, 0x90, 0x2B, 0x80, 0xBF, 0x1F,
		0x00, 0xC1, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		0x9C, 0x8E, 0x8F, 0x14, 0x00, 0x96, 0xB9, 0xA2,
		0xFF, 
	/* GC */
		0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x0F, 0x0F,
		0xFF, 
	/* AC */
		0x00, 0x13, 0x15, 0x17, 0x02, 0x04, 0x06, 0x07,
		0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
		0x01, 0x00, 0x03, 0x00, 0x00, 
	};

//PALETTE
unsigned char palette04H[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 
    0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 
    0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 
    0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
    0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 
    0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x2A, 0x00, 0x2A, 
    0x00, 0x00, 0x2A, 0x2A, 0x2A, 0x00, 0x00, 0x2A, 0x00, 0x2A, 0x2A, 0x15, 0x00, 0x2A, 0x2A, 0x2A, 
    0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 
    0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x15, 0x15, 0x15, 0x3F, 0x15, 0x3F, 
    0x15, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x15, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 0x15, 0x3F, 0x3F, 0x3F, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

//DOUBLE BUFFER POINTER;

unsigned char *MODE04H_BUFFER[] = {NULL, NULL};
unsigned char bufferTurnedOn04H = 0;

int8_t setMode04H()
{
    writeRegisters(g_320x200x4c);
    set_vga_palette(palette04H);
    clearScreen04H();
    setTurnOnBufferFunc(&turnOnBuffer04H);
    setTurnOffBufferFunc(&turnOffBuffer04H);
    setIsBufferOnFunc(&isBufferOn04H);
    setSwapBuffersFunc(&swapBuffers04H);
    setDrawPixelFunc(&drawPixel04H);
    setDrawLineFunc(&drawLine04H);
    setDrawCircleFunc(&drawCircle04H);
    setDrawRectangleFunc(&drawRectangle04H);
    setClearScreenFunc(&clearScreen04H);
    return 0x04;
}

int8_t turnOnBuffer04H()
{
    if(bufferTurnedOn04H) return -1;
    for(int i = 1; i >= 0; i--)
    {
        MODE04H_BUFFER[i] = heap_kernel_alloc(MODE04H_HEIGHT * MODE04H_WIDTH / 8, 0);
        if(MODE04H_BUFFER[i] == NULL)
        {
            for(int j = 1; j >= i; j--)
            {
                heap_kernel_dealloc(MODE04H_BUFFER[j]);
                MODE04H_BUFFER[j] = NULL;
            }
            return -1;
        }
    }
    setDrawPixelFunc(&drawPixel04HBuffered);
    setDrawLineFunc(&drawLine04HBuffered);
    setDrawCircleFunc(&drawCircle04HBuffered);
    setDrawRectangleFunc(&drawRectangle04HBuffered);
    setClearScreenFunc(&clearScreen04HBuffered);
    bufferTurnedOn04H = 1;
    return 0;
}

int8_t turnOffBuffer04H()
{
    if(!bufferTurnedOn04H) return -1;
    for(int i = 1; i >= 0; i--)
    {
        heap_kernel_dealloc(MODE04H_BUFFER[i]);
        MODE04H_BUFFER[i] = NULL;
    }
    setDrawPixelFunc(&drawPixel04H);
    setDrawLineFunc(&drawLine04H);
    setDrawCircleFunc(&drawCircle04H);
    setDrawRectangleFunc(&drawRectangle04H);
    setClearScreenFunc(&clearScreen04H);
    bufferTurnedOn04H = 0;
    return 0;
}

uint8_t isBufferOn04H()
{
    return bufferTurnedOn04H;
}

int8_t swapBuffers04H()
{
    if(!bufferTurnedOn04H) return -1;
    memcpy(VGA_VRAM_2, MODE04H_BUFFER[0], MODE04H_WIDTH * MODE04H_HEIGHT / 8);
    memcpy(VGA_VRAM_2 + 0x2000, MODE04H_BUFFER[1], MODE04H_WIDTH * MODE04H_HEIGHT / 8);
    //memcpy(VGA_VRAM, MODE13H_BUFFER, MODE13H_HEIGHT * MODE13H_WIDTH);
    return 0;
}

int8_t drawPixel04H(uint8_t color, uint16_t x, uint16_t y)
{
    if((x>=MODE04H_WIDTH) || (y >=MODE04H_HEIGHT))
        return -1;
    unsigned char *fb = (unsigned char *) VGA_VRAM_2;
    unsigned int offset = (y/2 * MODE04H_WIDTH + x)/4;
	unsigned bit_no = x % 4;
	bit_write(fb[offset + (y%2 ? 0x2000 : 0)], 1<<(7 - (2 * bit_no)), (color & 0x2));
	bit_write(fb[offset + (y%2 ? 0x2000 : 0)], 1<<(7 - (2 * bit_no+1)), (color & 0x1));
    return 0;
}

int8_t drawLine04H(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}

int8_t drawCircle04H(uint8_t color, uint16_t x, uint16_t y, uint16_t radius) 
{
    return 0;
}

int8_t drawRectangle04H(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t clearScreen04H()
{
    memset(VGA_VRAM_2, 0, 8000);
    memset(VGA_VRAM_2 + 0x2000, 0, 8000);
    return 0;
}

int8_t drawPixel04HBuffered(uint8_t color, uint16_t x, uint16_t y)
{
    if((!bufferTurnedOn04H) || (x>=MODE04H_WIDTH) || (y >=MODE04H_HEIGHT))
        return -1;
    unsigned int offset = (y * MODE04H_WIDTH + x)/4;
	unsigned bit_no = x % 4;
    bit_write(MODE04H_BUFFER[y%2][offset], (1<<(7 - (2 * bit_no))), (color & 0x2));
    bit_write(MODE04H_BUFFER[y%2][offset], (1<<(7 - (2 * bit_no+1))), (color & 0x1));
    return 0;
}

int8_t drawLine04HBuffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t drawCircle04HBuffered(uint8_t color, uint16_t x, uint16_t y, uint16_t radius)
{
    return 0;
}
int8_t drawRectangle04HBuffered(uint8_t color, uint16_t ax, uint16_t ay, uint16_t bx, uint16_t by)
{
    return 0;
}
int8_t clearScreen04HBuffered()
{
    if(!bufferTurnedOn04H) return -1;
    memset(MODE04H_BUFFER[0], 0, 8000);
    memset(MODE04H_BUFFER[1], 0, 8000);
    return 0;
}