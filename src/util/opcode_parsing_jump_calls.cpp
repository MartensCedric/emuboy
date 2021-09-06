//
// Created by cedric on 2021-08-17.
//

/**
 * To understand what is going in this file, it is critical that
 * the reader follows with this table:
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

#include <memory/memory_management_unit.h>
#include <cpu/CPU.h>
#include <util/opcode_parsing_math.h>

void register_jump_calls_opcodes(CPU *cpu) {
    cpu->register_opcode("JR r8",
                         [](uint16_t opcode) { return opcode == 0x18; },
                         [](CPU *cpu) {
                             cpu->jump_to_address(
                                     cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("JR NZ r8",
                         [](uint16_t opcode) { return opcode == 0x20; },
                         [](CPU *cpu) {
                             if (!cpu->is_zero_flag_on())
                                 cpu->jump_to_address(
                                         cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("JR Z r8",
                         [](uint16_t opcode) { return opcode == 0x28; },
                         [](CPU *cpu) {
                             if (cpu->is_zero_flag_on())
                                 cpu->jump_to_address(
                                         cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("JR NC r8",
                         [](uint16_t opcode) { return opcode == 0x30; },
                         [](CPU *cpu) {
                             if (!cpu->is_carry_flag_on())
                                 cpu->jump_to_address(
                                         cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("JR NC r8",
                         [](uint16_t opcode) { return opcode == 0x30; },
                         [](CPU *cpu) {
                             if (!cpu->is_carry_flag_on())
                                 cpu->jump_to_address(
                                         cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("JR C r8",
                         [](uint16_t opcode) { return opcode == 0x38; },
                         [](CPU *cpu) {
                             if (cpu->is_carry_flag_on())
                                 cpu->jump_to_address(
                                         cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
                         });

    cpu->register_opcode("RST",
                         [](uint16_t opcode) {
                             return byte_in_range_vertical(opcode, 0xC7, 0xF7) ||
                                    byte_in_range_vertical(opcode, 0xCF, 0xFF);
                         },
                         [](CPU *cpu) {
                             cpu->push(cpu->get_program_counter());
                             cpu->jump_to_address(cpu->fetch_byte() - 0xC7);
                         });

    cpu->register_opcode("RET NZ",
                         [](uint16_t opcode) { return opcode == 0xC0; },
                         [](CPU *cpu) {
                             if (!cpu->is_zero_flag_on())
                                 cpu->jump_to_address(cpu->pop());
                         });

    cpu->register_opcode("JP NZ a16",
                         [](uint16_t opcode) { return opcode == 0xC2; },
                         [](CPU *cpu) {
                             if (!cpu->is_zero_flag_on())
                                 cpu->jump_to_address(cpu->fetch_next_word());
                         });

    cpu->register_opcode("JP a16",
                         [](uint16_t opcode) { return opcode == 0xC3; },
                         [](CPU *cpu) {
                             cpu->jump_to_address(cpu->fetch_next_word());
                         });

    cpu->register_opcode("CALL NZ a16",
                         [](uint16_t opcode) { return opcode == 0xC4; },
                         [](CPU *cpu) {
                             if (!cpu->is_zero_flag_on()) {
                                 cpu->call(cpu->fetch_next_word());
                             }
                         });

    cpu->register_opcode("RET Z",
                         [](uint16_t opcode) { return opcode == 0xC8; },
                         [](CPU *cpu) {
                             if (cpu->is_zero_flag_on())
                                 cpu->jump_to_address(cpu->pop());
                         });

    cpu->register_opcode("RET",
                         [](uint16_t opcode) { return opcode == 0xC9; },
                         [](CPU *cpu) {
                             cpu->jump_to_address(cpu->pop());
                         });

    cpu->register_opcode("JP Z a16",
                         [](uint16_t opcode) { return opcode == 0xCA; },
                         [](CPU *cpu) {
                             if (cpu->is_zero_flag_on())
                                 cpu->jump_to_address(cpu->fetch_next_word());
                         });

    cpu->register_opcode("ADC A d8",
                         [](uint16_t opcode) { return opcode == 0xCE; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->add_carry_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                           cpu->fetch_next_byte());
                         });

    cpu->register_opcode("RET NC",
                         [](uint16_t opcode) { return opcode == 0xD0; },
                         [](CPU *cpu) {
                             if (!cpu->is_carry_flag_on())
                                 cpu->jump_to_address(cpu->pop());
                         });

    cpu->register_opcode("JP NC a16",
                         [](uint16_t opcode) { return opcode == 0xD2; },
                         [](CPU *cpu) {
                             if (!cpu->is_carry_flag_on())
                                 cpu->jump_to_address(cpu->fetch_next_word());
                         });

    cpu->register_opcode("CALL NC a16",
                         [](uint16_t opcode) { return opcode == 0xD4; },
                         [](CPU *cpu) {
                             if (!cpu->is_carry_flag_on()) {
                                 cpu->call(cpu->fetch_next_word());
                             }
                         });

    cpu->register_opcode("RET C",
                         [](uint16_t opcode) { return opcode == 0xD8; },
                         [](CPU *cpu) {
                             if (cpu->is_carry_flag_on())
                                 cpu->jump_to_address(cpu->pop());
                         });

    cpu->register_opcode("RETI",
                         [](uint16_t opcode) { return opcode == 0xD9; },
                         [](CPU *cpu) {
                             cpu->jump_to_address(cpu->pop());
                             cpu->enable_interrupts();
                         });

    cpu->register_opcode("JP C a16",
                         [](uint16_t opcode) { return opcode == 0xDA; },
                         [](CPU *cpu) {
                             if (cpu->is_carry_flag_on())
                                 cpu->jump_to_address(cpu->fetch_next_word());
                         });

    cpu->register_opcode("SBC A d8",
                         [](uint16_t opcode) { return opcode == 0xDE; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->sub_carry_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                           cpu->fetch_next_byte());
                         });

    cpu->register_opcode("JP (HL)",
                         [](uint16_t opcode) { return opcode == 0xE9; },
                         [](CPU *cpu) {
                             cpu->jump_to_address(
                                     cpu->get_word_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX)));
                         });

    cpu->register_opcode("XOR A d8",
                         [](uint16_t opcode) { return opcode == 0xEE; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_xor_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
                         });

    cpu->register_opcode("CP A d8",
                         [](uint16_t opcode) { return opcode == 0xFE; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_xor_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
                         });

}
