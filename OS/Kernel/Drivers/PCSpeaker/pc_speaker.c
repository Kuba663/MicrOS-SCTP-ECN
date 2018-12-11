#include "pc_speaker.h"
#include "../../Assembly/io.h"

uint16_t old_value = 0;

void pc_speaker_sound(uint32_t freq)
{
	uint32_t Div;
	uint8_t tmp;

	Div = 1193180 / freq;
	io_out_byte(0x43, 0xb6);
	old_value = io_in_byte(0x42);
	old_value |= ((uint16_t)io_in_byte(0x42)) << 8;
	io_out_byte(0x42, (uint8_t)(Div));
	io_out_byte(0x42, (uint8_t)(Div >> 8));

	tmp = io_in_byte(0x61);
	if (tmp != (tmp | 3))
	{
		io_out_byte(0x61, tmp | 3);
	}
}

void pc_speaker_no_sound()
{
	uint8_t tmp = io_in_byte(0x61) & 0xFC;
	io_out_byte(0x61, tmp);
	io_out_byte(0x43, 0xb6);
	io_out_byte(0x42, (uint8_t)(old_value));
	io_out_byte(0x42, (uint8_t)(old_value >> 8));
}