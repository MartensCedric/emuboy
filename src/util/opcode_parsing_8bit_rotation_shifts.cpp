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

void call_8bit_rotation_shifts(CPU *cpu) {
    uint8_t first_byte = cpu->fetch_byte();

    if (first_byte == 0x07) {
        // todo: RLCA
    } else if (first_byte == 0x17) {
        // todo: RLA
    } else if (first_byte == 0xCB) {
        uint8_t second_byte = cpu->fetch_next_byte();
        if (byte_in_range_matrix(second_byte, 0x40, 0x73)) {
            uint8_t bit_to_test = (((second_byte & 0xF0) >> 4) - 0x04) * 2;
            uint8_t register_x = second_byte & 0x0F;
            cpu->get_shifting_unit()->test_bit_register(bit_to_test, register_x);
        } else if (byte_in_range_matrix(second_byte, 0x80, 0xB3)) {
            uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
            uint8_t register_x = second_byte & 0x0F;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, register_x);
        } else if (byte_in_range_vertical(second_byte, 0x8C, 0xBC)) {
            uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_H_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0x8D, 0xBD)) {
            uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_L_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0x8F, 0xBF)) {
            uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_A_INDEX);
        } else if (byte_in_range_matrix(second_byte, 0xC0, 0xF3)) {
            uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
            uint8_t register_x = second_byte & 0x0F;
            cpu->get_shifting_unit()->set_bit_register(bit_to_set, register_x);
        } else if (byte_in_range_vertical(second_byte, 0x44, 0x74)) {
            uint8_t bit_to_test = (((second_byte & 0xF0) >> 4) - 0x04) * 2;
            cpu->get_shifting_unit()->test_bit_register(bit_to_test, REGISTER_H_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0x84, 0xB4)) {
            uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_H_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0x85, 0xB5)) {
            uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_L_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0x87, 0xB7)) {
            uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_A_INDEX);
        } else if (byte_in_range_matrix(second_byte, 0x88, 0xBB)) {
            uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
            uint8_t register_x = (second_byte - 0x08) & 0x0F;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, register_x);
        } else if (byte_in_range_vertical(second_byte, 0xC4, 0xF4)) {
            uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
            cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_H_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0xC5, 0xF5)) {
            uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
            cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_L_INDEX);
        } else if (byte_in_range_vertical(second_byte, 0xC7, 0xF7)) {
            uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
            cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_A_INDEX);
        } else if (byte_in_range_matrix(second_byte, 0xC8, 0xFB)) {
            uint8_t bit_to_set = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
            uint8_t register_x = (second_byte - 0x08) & 0x0F;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_set, register_x);
        }

    }
}