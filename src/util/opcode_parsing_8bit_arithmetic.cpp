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

void register_8bit_arithmetic_opcodes(CPU *cpu) {


    cpu->register_opcode("INC Registers 0x04-0x24",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x04, 0x24); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) * 2u) + ((first_byte & 0x08u) >> 3u);
                             cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
                         });

    cpu->register_opcode("DEC Registers 0x05-0x25",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x05, 0x25); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) * 2u) + ((first_byte & 0x08u) >> 3u);
                             cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
                         });

    cpu->register_opcode("INC Registers 0x0C-0x3C",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x0C, 0x3C); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) * 2) + ((first_byte & 0x08u) >> 3u);
                             cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
                         });

    cpu->register_opcode("DEC Registers 0x0D-0x3D",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x0D, 0x3D); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) * 2u) + ((first_byte & 0x08u) >> 3u);
                             cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
                         });

    cpu->register_opcode("CPL",
                         [](uint16_t opcode) { return opcode == 0x2F; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->complement_register(REGISTER_A_INDEX);
                         });

    cpu->register_opcode("INC (HL)",
                         [](uint16_t opcode) { return opcode == 0x34; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->increment_indirect_8bit(
                                     cpu->get_16bit_register(REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("DEC (HL)",
                         [](uint16_t opcode) { return opcode == 0x35; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->decrement_indirect_8bit(
                                     cpu->get_16bit_register(REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("SCF",
                         [](uint16_t opcode) { return opcode == 0x37; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->set_carry_flag();
                         });

    cpu->register_opcode("CCF",
                         [](uint16_t opcode) { return opcode == 0x3F; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->complement_carry_flag();
                         });

    cpu->register_opcode("ADC Registers 0x88-0x8D",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x88, 0x8D); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_arithmetic_unit()->add_carry_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                           (first_byte - 8u) & 0xFu);
                         });

    cpu->register_opcode("ADD Registers 0x80-0x85",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x80, 0x85); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_arithmetic_unit()->add_registers_8bit(REGISTER_A_INDEX, first_byte & 0xFu);
                         }
    );

    cpu->register_opcode("ADD A (HL)",
                         [](uint16_t opcode) { return opcode == 0x86; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->add_register_indirect_8bit(REGISTER_A_INDEX,
                                                                                    cpu->get_16bit_register(
                                                                                            REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("ADD A A",
                         [](uint16_t opcode) { return opcode == 0x87; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->add_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("SBC Registers 0x98-0x9D",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x98, 0x9D); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_arithmetic_unit()->add_carry_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                           (first_byte - 8u) & 0xFu);
                         });

    cpu->register_opcode("ADC A (HL)",
                         [](uint16_t opcode){ return opcode == 0x8E;},
                         [](CPU *cpu){
                            cpu->get_arithmetic_unit()->add_carry_register_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    });

    cpu->register_opcode("ADC A A",
                         [](uint16_t opcode){ return opcode == 0x8F;},
                         [](CPU *cpu){
                             cpu->get_arithmetic_unit()->add_carry_register_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("SBC A (HL)",
                         [](uint16_t opcode){ return opcode == 0x9E;},
                         [](CPU *cpu){
                             cpu->get_arithmetic_unit()->sub_carry_register_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("SBC A A",
                         [](uint16_t opcode){ return opcode == 0x9F;},
                         [](CPU *cpu){
                             cpu->get_arithmetic_unit()->sub_carry_register_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("AND Registers 0xA0-0xA5",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0xA0, 0xA5); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
                             uint8_t value_to_and = cpu->get_registers()[first_byte & 0xFu];

                             uint8_t new_value = original_value & value_to_and;
                             cpu->load_register_immediate(REGISTER_A_INDEX, new_value);
                         });

    cpu->register_opcode("SUB Registers 0x90-0x95",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x90, 0x95); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, first_byte & 0xFu);
                         });

    cpu->register_opcode("SUB A (HL)",
                         [](uint16_t opcode) { return opcode == 0x96; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_and_memory_indirect_8bit(REGISTER_A_INDEX,
                                                                                   cpu->get_16bit_register(
                                                                                           REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("SUB A A",
                         [](uint16_t opcode) { return opcode == 0x97; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("AND A (HL)",
                         [](uint16_t opcode) { return opcode == 0xA6; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_and_memory_indirect_8bit(REGISTER_A_INDEX,
                                                                                   cpu->get_16bit_register(
                                                                                           REGISTER_HL_INDEX));
                         });
    cpu->register_opcode("AND A A",
                         [](uint16_t opcode) { return opcode == 0xA7; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_and_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("XOR Registers 0xA8-0xAD",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0xA8, 0xAD); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, (first_byte - 8u) & 0xFu);
                         });

    cpu->register_opcode("XOR A (HL)",
                         [](uint16_t opcode) { return opcode == 0xAE; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_xor_memory_indirect_8bit(REGISTER_A_INDEX,
                                                                                   cpu->get_16bit_register(
                                                                                           REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("XOR A A",
                         [](uint16_t opcode) { return opcode == 0xAF; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_xor_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("OR Registers 0xB0-0xB5",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0xB0, 0xB5); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, (first_byte - 8u) & 0xFu);
                         });

    cpu->register_opcode("OR A (HL)",
                         [](uint16_t opcode) { return opcode == 0xB6; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_or_memory_indirect_8bit(REGISTER_A_INDEX,
                                                                                  cpu->get_16bit_register(
                                                                                          REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("OR A A",
                         [](uint16_t opcode) { return opcode == 0xB7; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("CP Registers 0xB8-0xBD",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0xB8, 0xBD); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_logic_unit()->compare_registers_8bit(REGISTER_A_INDEX, (first_byte - 8u) & 0xFu);
                         });

    cpu->register_opcode("CP A (HL)",
                         [](uint16_t opcode) { return opcode == 0xBE; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->compare_memory_indirect_8bit(REGISTER_A_INDEX,
                                                                                 cpu->get_16bit_register(
                                                                                         REGISTER_HL_INDEX));
                         });

    cpu->register_opcode("CP A A",
                         [](uint16_t opcode) { return opcode == 0xBF; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->compare_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("ADD A d8",
                         [](uint16_t opcode) { return opcode == 0xC6; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->add_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                     cpu->fetch_next_byte());
                         });

    cpu->register_opcode("SUB A d8",
                         [](uint16_t opcode) { return opcode == 0xD6; },
                         [](CPU *cpu) {
                             cpu->get_arithmetic_unit()->sub_register_immediate_8bit(REGISTER_A_INDEX,
                                                                                     cpu->fetch_next_byte());
                         });

    cpu->register_opcode("AND A d8",
                         [](uint16_t opcode) { return opcode == 0xE6; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_and_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
                         });

    cpu->register_opcode("OR A d8",
                         [](uint16_t opcode) { return opcode == 0xF6; },
                         [](CPU *cpu) {
                             cpu->get_logic_unit()->logic_or_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
                         });

}
