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
#include <util/opcode_parsing_8bit_rotation_shifts.h>

void register_8bit_rotation_shifts_opcodes(CPU *cpu) {

    cpu->register_opcode("BIT N REG 0xCB 0x40-0x73, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_matrix(opcode & 0xFF, 0x40, 0x73);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_test = (((second_byte & 0xF0) >> 4) - 0x04) * 2;
                             uint8_t register_x = second_byte & 0x0F;
                             cpu->get_shifting_unit()->test_bit_register(bit_to_test, register_x);
                         });

    cpu->register_opcode("RES N REG 0xCB 0x80-0xB3, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_matrix(opcode & 0xFF, 0x80, 0xB3);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
                             uint8_t register_x = second_byte & 0x0F;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, register_x);
                         });

    cpu->register_opcode("RES N H 0xCB 0x8C-0xBC, N is odd",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x8C, 0xBC);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_H_INDEX);
                         });

    cpu->register_opcode("RES N L 0xCB 0x8D-0xBD, N is odd",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x8D, 0xBD);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_L_INDEX);
                         });

    cpu->register_opcode("RES N A 0xCB 0x8F-0xBF, N is odd",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x8F, 0xBF);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("SET N REG 0xCB 0xC0-0xF3, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_matrix(opcode & 0xFF, 0xC0, 0xF3);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
                             uint8_t register_x = second_byte & 0x0F;
                             cpu->get_shifting_unit()->set_bit_register(bit_to_set, register_x);
                         });

    cpu->register_opcode("BIT N H 0xCB 0x44-0x74, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x44, 0x74);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_test = (((second_byte & 0xF0) >> 4) - 0x04) * 2;
                             cpu->get_shifting_unit()->test_bit_register(bit_to_test, REGISTER_H_INDEX);
                         });

    cpu->register_opcode("RES N H 0xCB 0x84-0xB4, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x84, 0xB4);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_H_INDEX);
                         });

    cpu->register_opcode("RES N L 0xCB 0x85-0xB5, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x85, 0xB5);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_L_INDEX);
                         });

    cpu->register_opcode("RES N A 0xCB 0x87-0xB7, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0x87, 0xB7);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = (((second_byte & 0xF0) >> 4) - 0x08) * 2;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("RES N REG 0xCB 0x88-0xBB, N is odd",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_matrix(opcode & 0xFF, 0x88, 0xBB);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_reset = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
                             uint8_t register_x = (second_byte - 0x08) & 0x0F;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, register_x);
                         });

    cpu->register_opcode("SET N H 0xCB 0xC4-0xF4, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0xC4, 0xF4);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
                             cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_H_INDEX);
                         });

    cpu->register_opcode("SET N L 0xCB 0xC5-0xF5, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0xC5, 0xF5);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
                             cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_L_INDEX);
                         });

    cpu->register_opcode("SET N A 0xCB 0xC7-0xF7, N is even",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0xC7, 0xF7);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_set = (((second_byte & 0xF0) >> 4) - 0x0C) * 2;
                             cpu->get_shifting_unit()->set_bit_register(bit_to_set, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("SET N A 0xCB 0xC8-0xF8, N is odd",
                         [](uint16_t opcode) {
                             return ((opcode & 0xFF00) == 0xCB00) &&
                                    byte_in_range_vertical(opcode & 0xFF, 0xC7, 0xF7);
                         },
                         [](CPU *cpu) {
                             uint8_t second_byte = (cpu->fetch_word() & 0xFF00) >> 8;
                             uint8_t bit_to_set = ((((second_byte & 0xF0) >> 4) - 0x08) * 2) + 1;
                             uint8_t register_x = (second_byte - 0x08) & 0x0F;
                             cpu->get_shifting_unit()->reset_bit_register(bit_to_set, register_x);
                         });
}
