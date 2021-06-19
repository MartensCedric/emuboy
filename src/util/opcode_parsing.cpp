//
// Created by cedric on 2021-06-19.
//

#include "opcode_parsing.h"
#include "opcode_parsing_math.h"

void call_8bit_lsm(CPU* cpu)
{
    // todo: Find a better way to do this, and not make it look like fetches
    uint8_t first_byte = cpu->fetch();
    cpu->increment_pc();
    uint8_t second_byte = cpu->fetch();
    cpu->increment_pc();
    uint8_t third_byte = cpu->fetch();


    /**
     *
     * reg[0]: B 06 0000 0100
     * reg[1]: C 0E 0000 1110
     * reg[2]: D 16 0001 0100
     * reg[3]: E 1E 0001 1110
     * reg[4] H 26 0010 0100
     * reg[5] L 2E 0010 1110
     *
     */

    if(byte_in_range_vertical(first_byte, 0x06, 0x26))
        cpu->load_immediate(((second_byte & 0xF0) * 2) + ((second_byte & 0x02) >> 1), third_byte);
}