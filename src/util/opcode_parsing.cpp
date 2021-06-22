//
// Created by cedric on 2021-06-19.
//

#include "opcode_parsing.h"
#include "opcode_parsing_math.h"

void call_8bit_lsm(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    if(byte_in_range_matrix(first_byte, 0x40, 0x65))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        const uint8_t reg_y = first_byte & 0xF;
        cpu->load_register_indirect(reg_x, reg_y);
    }
    else if(byte_in_range_matrix(first_byte, 0x48, 0x6D))
    {
        const uint8_t reg_x = 1 + (((first_byte & 0xF0) >> 4) - 4) * 2;
        const uint8_t reg_y = (first_byte & 0xF) - 8;
        cpu->load_register_indirect(reg_x, reg_y);
    }
    else if(byte_in_range_vertical(first_byte, 0x46, 0x66))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_memory_indirect(reg_x, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(byte_in_range_vertical(first_byte, 0x47, 0x67))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_register_indirect(reg_x, REGISTER_A_INDEX);
    }
    else if(byte_in_range_vertical(first_byte, 0x06, 0x26) ||
        byte_in_range_vertical(first_byte, 0x0E, 0x3E))
    {
        const uint8_t reg_x = (((cpu->fetch() & 0xF0) >> 4) * 2) + ((cpu->fetch() & 0x08) >> 3);
        cpu->load_immediate(reg_x, cpu->fetch_next());
    }
    else if(byte_in_range(first_byte, 0x78, 0x7D))
        cpu->load_register_indirect(REGISTER_A_INDEX, first_byte - 0x78);
}