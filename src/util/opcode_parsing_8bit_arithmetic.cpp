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

    cpu->register_opcode("INC Registers 0x04-0x34",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x04, 0x24); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
                             cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
                         });

    cpu->register_opcode("ADD Registers 0x80-0x85",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x80, 0x85); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->get_arithmetic_unit()->add_registers_8bit(REGISTER_A_INDEX, first_byte & 0xF);
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

    cpu->register_opcode("AND Registers 0xA0-0xA5",
                         [](uint16_t opcode){ return byte_in_range(opcode, 0xA0, 0xA5); },
                         [](CPU* cpu){
                             uint8_t first_byte = cpu->fetch_byte();
                             uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
                             uint8_t value_to_and = cpu->get_registers()[first_byte & 0xF];

                             uint8_t new_value = original_value & value_to_and;
                             cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

    });
}

void call_8bit_arithmetic(CPU *cpu) {
    uint8_t first_byte = cpu->fetch_byte();
    if (first_byte == 0x96) {
        cpu->get_logic_unit()->logic_and_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    } else if (first_byte == 0x97) {
        cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    } else if (first_byte == 0xA6) {
        cpu->get_logic_unit()->logic_and_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    } else if (first_byte == 0xA7) {
        cpu->get_logic_unit()->logic_and_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    } else if (first_byte == 0xB6) {
        cpu->get_logic_unit()->logic_or_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    } else if (first_byte == 0xB7) {
        cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    } else if (first_byte == 0x2F) {
        cpu->get_logic_unit()->complement_register(REGISTER_A_INDEX);
    } else if (byte_in_range(first_byte, 0x90, 0x95)) {
        cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, first_byte & 0xF);
    } else if (byte_in_range(first_byte, 0xA8, 0xAD)) {
        cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    } else if (byte_in_range(first_byte, 0xB0, 0xB5)) {
        cpu->get_logic_unit()->logic_xor_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    } else if (byte_in_range(first_byte, 0xB8, 0xBD)) {
        cpu->get_logic_unit()->compare_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    } else if (first_byte == 0xC6) {
        cpu->get_arithmetic_unit()->add_register_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    } else if (first_byte == 0xD6) {
        cpu->get_arithmetic_unit()->sub_register_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    } else if (first_byte == 0xE6) {
        cpu->get_logic_unit()->logic_and_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    } else if (first_byte == 0xF6) {
        cpu->get_logic_unit()->logic_or_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    } else if (byte_in_range_vertical(first_byte, 0x05, 0x25)) {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
    } else if (byte_in_range_vertical(first_byte, 0x0C, 0x3C)) {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
    } else if (byte_in_range_vertical(first_byte, 0x0D, 0x3D)) {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
    } else if (first_byte == 0x34) {
        cpu->get_arithmetic_unit()->increment_indirect_8bit(cpu->get_16bit_register(REGISTER_HL_INDEX));
    } else if (first_byte == 0x35) {
        cpu->get_arithmetic_unit()->decrement_indirect_8bit(cpu->get_16bit_register(REGISTER_HL_INDEX));
    } else if (first_byte == 0x37) {
        cpu->get_logic_unit()->set_carry_flag();
    } else if (first_byte == 0x3F) {
        cpu->get_logic_unit()->complement_carry_flag();
    } else if (byte_in_range(first_byte, 0x88, 0x8D)) {
        cpu->get_arithmetic_unit()->add_carry_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    } else if (byte_in_range(first_byte, 0x98, 0x9D)) {
        cpu->get_arithmetic_unit()->add_carry_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }

}