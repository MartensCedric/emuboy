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

void register_16bit_arithmetic_opcodes(CPU *cpu) {

    cpu->register_opcode("INC 16bit Registers",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode & 0xFF, 0x03, 0x33); },
                         [](CPU *cpu) {
                             uint8_t reg_x = ((cpu->fetch_byte() & 0xF0) >> 4) + 1;
                             uint16_t value = cpu->get_16bit_register(reg_x);
                             value++;
                             cpu->load_16bit_register_immediate(reg_x, value);
                         });

    cpu->register_opcode("DEC 16bit Registers",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode & 0xFF, 0x0B, 0x3B); },
                         [](CPU *cpu) {
                             uint8_t reg_x = ((cpu->fetch_byte() & 0xF0) >> 4) + 1;
                             uint16_t value = cpu->get_16bit_register(reg_x);
                             value--;
                             cpu->load_16bit_register_immediate(reg_x, value);
                         });

    cpu->register_opcode("ADD HL 16bit Registers",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode & 0xFF, 0x09, 0x39); },
                         [](CPU *cpu) {
                             uint8_t reg_x = ((cpu->fetch_byte() & 0xF0) >> 4) + 1;
                             uint16_t value_added = cpu->get_16bit_register(reg_x);
                             uint16_t base_value = cpu->get_16bit_register(REGISTER_HL_INDEX);
                             uint16_t final_value = base_value + value_added;
                             // cpu->setSubtractFlag(false);
                             // cpu->setCarryFlag(final_value < base_value);
                             // cpu->setHalfCarryFlag(((base_value & 0xF) + (final_value & 0xF)) < (base_value & 0xF));
                             cpu->load_16bit_register_immediate(REGISTER_HL_INDEX, final_value);
                         });

    cpu->register_opcode("LD (a16) SP",
                         [](uint16_t opcode) { return opcode == 0xE8; },
                         [](CPU *cpu) {
                             uint16_t base_value = cpu->get_16bit_register(REGISTER_SP_INDEX);
                             uint16_t value_added = static_cast<uint16_t>(cpu->fetch_next_byte());
                             uint16_t final_value = base_value + value_added;
                             cpu->load_16bit_register_immediate(REGISTER_SP_INDEX, final_value);
                             //        cpu->setZeroFlag(false);
                             //        cpu->setSubtractFlag(false);
                             //        cpu->setCarryFlag(final_value < base_value);
                             //        cpu->setHalfCarryFlag(((base_value & 0xF) + (final_value & 0xF)) < (base_value & 0xF));
                         });

}