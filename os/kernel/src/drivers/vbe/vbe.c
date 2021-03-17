#include "vbe.h"
#include "../v8086/v8086.h"
#include "../v8086/memory_operations.h"
#include <stdbool.h>
#include <string.h>
#include "../memory/heap/heap.h"

v8086* machine = NULL;
bool initialized = false;
int currentBank = -1;
uint8_t* mem_buff = (uint8_t*)0xc0000000 + 0xA0000;

void VBE_initialize()
{
    if(!initialized)
    {
        machine = v8086_create_machine();
        if(machine == NULL) return;
        v8086_set_386_instruction_set(machine);
        initialized = true;
    }
}

void VBE_close()
{
    if(initialized)
    {
        v8086_destroy_machine(machine);
        initialized = false;
    }
}

bool VBE_is_initialized()
{
    return initialized;
}

VBEStatus VBE_check_existance_of_VESA()
{
    if(!initialized) return VBE_NO_INITAILIZED;
    machine->regs.x.ax = 0x4f03;
    v8086_call_int(machine, 0x10);
    if(machine->regs.x.ax != 0x004f) return VBE_NOT_EXIST;
    return VBE_OK;
}

VBEStatus VBE_get_svga_information(svga_information** information_struct_ptr){
    if(!initialized) return VBE_NO_INITAILIZED;
    svga_information* information_struct = heap_kernel_alloc(sizeof(svga_information), 0);
    if(information_struct == NULL) return VBE_INTERNAL_ERROR;
    machine->regs.x.ax = 0x4f00;
    machine->sregs.es = 0x0000;
    machine->regs.x.di = 0x7E00;
    int16_t status = v8086_call_int(machine, 0x10);
    if(status != 0x10) return VBE_INTERNAL_ERROR;
    if(machine->regs.h.al != 0x4f) return VBE_NOT_EXIST;
    if(machine->regs.h.ah != 0x00) return VBE_FUNCTION_FAILURE;
    *(uint32_t*)(information_struct->signature) = read_dword_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E00));
    information_struct->signature[5] = '\0';
    information_struct->vesa_standard_number = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E04));
    uint16_t off = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E06));
    uint16_t seg = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E08));
    uint16_t len = strlen(machine->Memory + get_absolute_address(seg, off));
    information_struct->producent_text = heap_kernel_alloc(len + 1, 0);
    strcpy(information_struct->producent_text, machine->Memory + get_absolute_address(seg, off));
    information_struct->additional_info = read_dword_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E0A));
    off = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E0E));
    seg = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E10));
    for(len = 0; read_word_from_pointer(machine->Memory, get_absolute_address(seg, off + 2*len)) != 0xffff; ++len);
    information_struct->number_of_modes = len;
    information_struct->mode_array = heap_kernel_alloc(2 * len, 0);
    memcpy(information_struct->mode_array, machine->Memory + get_absolute_address(seg, off), len * 2);
    *information_struct_ptr = information_struct;
    return VBE_OK;
}

VBEStatus VBE_get_vesa_mode_information(svga_mode_information* infromation_struct, uint16_t mode_number)
{
    if(!initialized) return VBE_NO_INITAILIZED;
    machine->regs.x.ax = 0x4f01;
    machine->regs.x.cx = mode_number;
    machine->sregs.es = 0x0000;
    machine->regs.x.di = 0x7E00;
    int16_t status = v8086_call_int(machine, 0x10);
    if(status != 0x10) return VBE_INTERNAL_ERROR;
    if(machine->regs.h.al != 0x4f) return VBE_NOT_EXIST;
    if(machine->regs.h.ah != 0x00) return VBE_FUNCTION_FAILURE;
    infromation_struct->mode_attributes = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E00));
    infromation_struct->window_a_attributes = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E02));
    infromation_struct->window_b_attributes = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E03));
    infromation_struct->granularity = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E04));
    infromation_struct->windows_size = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E06));
    infromation_struct->segment_of_window_a = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E08));
    infromation_struct->segment_of_window_b = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E0A));
    infromation_struct->far_pointer_to_bank_swap_function = read_dword_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E0C));
    infromation_struct->logical_line_length = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E10));
    infromation_struct->mode_width = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E12));
    infromation_struct->mode_height = read_word_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E14));
    infromation_struct->char_matrix_width = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E16));
    infromation_struct->char_matrix_height = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E17));
    infromation_struct->plane_count = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E18));
    infromation_struct->bits_per_pixel = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E19));
    infromation_struct->bank_count = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E1A));
    infromation_struct->memory_organization = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E1B));
    infromation_struct->bank_size = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E1C));
    infromation_struct->page_count = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E1D));
    infromation_struct->reserved = read_byte_from_pointer(machine->Memory, get_absolute_address(0x0000, 0x7E1E));

    return VBE_OK;
}

uint16_t VBE_get_word(uint32_t seg, uint32_t offset)
{
    return read_word_from_pointer(machine->Memory, get_absolute_address(seg, offset));
}

VBEStatus VBE_destroy_svga_information(svga_information* svga_information_ptr)
{
    heap_kernel_dealloc(svga_information_ptr->mode_array);
    heap_kernel_dealloc(svga_information_ptr->producent_text);
    heap_kernel_dealloc(svga_information_ptr);
    return VBE_OK;
}

VBEStatus VBE_set_video_mode(uint16_t mode_number, bool clear_screen)
{
    if(!initialized) return VBE_NO_INITAILIZED;
    machine->regs.x.ax = 0x4f02;
    machine->regs.x.bx = mode_number & 0x7FFF;
    if(clear_screen) machine->regs.x.bx | 0x8000;
    int16_t status = v8086_call_int(machine, 0x10);
    if(status != 0x10) return VBE_INTERNAL_ERROR;
    if(machine->regs.h.al != 0x4f) return VBE_NOT_EXIST;
    if(machine->regs.h.ah != 0x00) return VBE_FUNCTION_FAILURE;
    currentBank = -1;
    return VBE_OK;
}

VBEStatus VBE_get_current_video_mode(uint16_t* mode_number)
{
    if(!initialized) return VBE_NO_INITAILIZED;
    machine->regs.x.ax = 0x4f03;
    int16_t status = v8086_call_int(machine, 0x10);
    if(status != 0x10) return VBE_INTERNAL_ERROR;
    if(machine->regs.h.al != 0x4f) return VBE_NOT_EXIST;
    if(machine->regs.h.ah != 0x00) return VBE_FUNCTION_FAILURE;
    *mode_number = machine->regs.x.bx;
    return VBE_OK;
}

void VBE_set_current_bank(uint32_t bank_number, uint32_t winsize, uint32_t granularity)
{
    if(bank_number != currentBank)
    {
        uint32_t banknum = bank_number * (winsize / granularity);
        machine->regs.x.ax = 0x4f05;
        machine->regs.x.bx = 0;
        machine->regs.x.dx = banknum;
        int16_t status = v8086_call_int(machine, 0x10);
        machine->regs.x.ax = 0x4f05;
        machine->regs.x.bx = 1;
        machine->regs.x.dx = banknum;
        status = v8086_call_int(machine, 0x10);
    }
}

void VBE_draw_pixel_8_8_8(uint32_t mode_width, uint32_t mode_height, uint32_t winsize, uint32_t granularity, uint32_t x, uint32_t y, uint8_t r, uint8_t g, uint8_t b)
{
    uint64_t l = (uint64_t) y * (mode_width * 3) + (x*3);
    VBE_set_current_bank((l>>10)/winsize, winsize, granularity);
    mem_buff[(uint32_t)l] = b;
    mem_buff[(uint32_t)l + 1] = g;
    mem_buff[(uint32_t)l + 2] = r;
}