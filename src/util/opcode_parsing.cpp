//
// Created by cedric on 2021-06-19.
//

#include "opcode_parsing.h"
#include "opcode_parsing_math.h"

void call_8bit_lsm(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    /**
     *
     * reg[0]: B 06 0000 0110
     * reg[1]: C 0E 0000 1110
     * reg[2]: D 16 0001 0110
     * reg[3]: E 1E 0001 1110
     * reg[4] H 26 0010 0110
     * reg[5] L 2E 0010 1110
     * reg[7] A 3E 0011 1110
     *
     */
    if(byte_in_range_vertical(first_byte, 0x06, 0x26) ||
        byte_in_range_vertical(first_byte, 0x0E, 0x3E))
    {
        const uint8_t reg_x = (((cpu->fetch() & 0xF0) >> 4) * 2) + ((cpu->fetch() & 0x08) >> 3);
        cpu->load_immediate(reg_x, cpu->fetch_next());
    }


    if(byte_in_range(first_byte, 0x78, 0x7D))
        cpu->load_register_indirect(REGISTER_A_INDEX, first_byte - 0x78);
}