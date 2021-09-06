//
// Created by cedric on 2021-08-17.
//

/**
 * To understand what is going in this file, it is critical that
 * the reader follows with this table:
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

#include <cpu/CPU.h>
#include <util/opcode_parsing_math.h>
#include "opcode_parsing_16bit_lsm.h"

void register_16bit_lsm_opcodes(CPU *cpu) {
    cpu->register_opcode("LD 16bit-REG d16",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x01, 0x31); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint16_t data = cpu->fetch_next_word();
                             cpu->load_16bit_register_immediate(1 + (first_byte >> 4), data);
                         });

    cpu->register_opcode("POP 16bit-REG",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0xC1, 0xF1); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
                             cpu->load_16bit_register_immediate(reg_x, cpu->pop());
                         });

    cpu->register_opcode("PUSH 16bit-REG",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0xC5, 0xF5); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
                             cpu->push(cpu->get_16bit_register(reg_x));
                         });

    cpu->register_opcode("LD SP HL",
                         [](uint16_t opcode) { return opcode == 0xF9; },
                         [](CPU *cpu) {
                             cpu->load_16bit_register_immediate(REGISTER_SP_INDEX,
                                                                cpu->get_16bit_register(REGISTER_HL_INDEX));
                         });
}