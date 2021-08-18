//
// Created by cedric on 2021-08-17.
//

#include <cpu/CPU.h>
#include <util/opcode_parsing_math.h>
#include "opcode_parsing_16bit_lsm.h"

void call_16bit_lsm(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(byte_in_range_vertical(first_byte, 0x01, 0x31))
    {
        uint16_t data = cpu->fetch_next_word();
        cpu->load_16bit_register_immediate(1 + (first_byte >> 4), data);
    }
    else if(byte_in_range_vertical(first_byte, 0xC1, 0xF1))
    {
        uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
        cpu->load_16bit_register_immediate(reg_x, cpu->pop());
    }
    else if(byte_in_range_vertical(first_byte, 0xC5, 0xF5))
    {
        uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
        cpu->push(cpu->get_16bit_register(reg_x));
    }
    else if(first_byte == 0xF9)
    {
        cpu->load_16bit_register_immediate(REGISTER_SP_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
}

