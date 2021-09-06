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

void register_8bit_lsm_opcodes(CPU *cpu) {
    cpu->register_opcode("LD (REG) A 0x2-0x12",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x02, 0x12); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = 1 + ((first_byte & 0xF0u) >> 4u);
                             cpu->store_memory_indirect(cpu->get_16bit_register(reg_x), REGISTER_A_INDEX);
                         });


    cpu->register_opcode("LD REG d8 0x06-0x26,0x0E-0x3E",
                         [](uint16_t opcode) {
                             return (byte_in_range_vertical(opcode, 0x06, 0x26) ||
                                     byte_in_range_vertical(opcode, 0x0E, 0x3E));
                         },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) * 2) + ((first_byte & 0x08u) >> 3u);
                             cpu->load_register_immediate(reg_x, cpu->fetch_next_byte());
                         }
    );


    cpu->register_opcode("LD (REG) A 0x0A-0x1A",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x0A, 0x1A); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = first_byte == 0x0A ? REGISTER_BC_INDEX : REGISTER_DE_INDEX;
                             cpu->load_memory_indirect(REGISTER_A_INDEX, cpu->get_16bit_register(reg_x));
                         });


    cpu->register_opcode("LD A (HL+-)",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x22, 0x32); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint16_t memory_address = cpu->get_16bit_register(REGISTER_HL_INDEX);
                             cpu->store_memory_indirect(memory_address, REGISTER_A_INDEX);

                             if (first_byte == 0x22)
                                 memory_address++;
                             else
                                 memory_address--;

                             cpu->load_16bit_register_immediate(REGISTER_HL_INDEX, memory_address);
                         });

    cpu->register_opcode("LD A (HL+-)",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x2A, 0x3A); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             uint16_t memory_address = cpu->get_16bit_register(REGISTER_HL_INDEX);
                             cpu->load_memory_indirect(REGISTER_A_INDEX, memory_address);

                             if (first_byte == 0x2A)
                                 memory_address++;
                             else
                                 memory_address--;

                             cpu->load_16bit_register_immediate(REGISTER_HL_INDEX, memory_address);
                         });

    cpu->register_opcode("LD (HL) d8",
                         [](uint16_t opcode) { return opcode == 0x36; },
                         [](CPU *cpu) {
                             cpu->store_memory_immediate(cpu->get_16bit_register(REGISTER_HL_INDEX),
                                                         cpu->fetch_next_byte());
                         });

    cpu->register_opcode("LD Registers 0x40 0x65",
                         [](uint16_t opcode) { return byte_in_range_matrix(opcode, 0x40, 0x65); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             const uint8_t reg_y = first_byte & 0xFu;
                             cpu->load_register_indirect(reg_x, reg_y);
                         });

    cpu->register_opcode("LD REG (HL) 0x46-0x66",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x46, 0x66); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             cpu->load_memory_indirect(reg_x, cpu->get_16bit_register(REGISTER_HL_INDEX));
                         }
    );

    cpu->register_opcode("LD REG A 0x47-0x67",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x47, 0x67); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             cpu->load_register_indirect(reg_x, REGISTER_A_INDEX);
                         }
    );

    cpu->register_opcode("LD Registers 0x48 0x6D",
                         [](uint16_t opcode) { return byte_in_range_matrix(opcode, 0x48, 0x6D); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = 1 + (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             const uint8_t reg_y = (first_byte & 0xFu) - 8;
                             cpu->load_register_indirect(reg_x, reg_y);
                         });


    cpu->register_opcode("LD REG (HL) 0x4E-0x7E",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x4E, 0x7E); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             cpu->load_memory_indirect(reg_x, cpu->get_16bit_register(REGISTER_HL_INDEX));
                         }
    );

    cpu->register_opcode("LD REG A 0x4F-0x7F",
                         [](uint16_t opcode) { return byte_in_range_vertical(opcode, 0x4F, 0x7F); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = (((first_byte & 0xF0u) >> 4u) - 4) * 2;
                             cpu->load_memory_indirect(reg_x, REGISTER_A_INDEX);
                         }
    );

    cpu->register_opcode("LD (HL) REG 0x70-0x75",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x70, 0x75); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             const uint8_t reg_x = first_byte & 0xFu;
                             cpu->store_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX), reg_x);
                         });

    cpu->register_opcode("LD (HL) A",
                         [](uint16_t opcode) { return opcode == 0x77; },
                         [](CPU *cpu) {
                             cpu->store_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX), REGISTER_A_INDEX);
                         });

    cpu->register_opcode("LD A REG 0x78-0x7D",
                         [](uint16_t opcode) { return byte_in_range(opcode, 0x78, 0x7D); },
                         [](CPU *cpu) {
                             uint8_t first_byte = cpu->fetch_byte();
                             cpu->load_register_indirect(REGISTER_A_INDEX, first_byte - 0x78);
                         });


    cpu->register_opcode("LD (HL) A",
                         [](uint16_t opcode) { return opcode == 0xE0; },
                         [](CPU *cpu) {
                             cpu->store_memory_indirect(0xFF00 + cpu->fetch_next_byte(), REGISTER_A_INDEX);
                         });

    cpu->register_opcode("LD (a16) A",
                         [](uint16_t opcode) { return opcode == 0xEA; },
                         [](CPU *cpu) {
                             uint16_t address = cpu->fetch_next_word();
                             cpu->store_memory_indirect(address, REGISTER_A_INDEX);
                         });

    cpu->register_opcode("LD (C) A",
                         [](uint16_t opcode) { return opcode == 0xE2; },
                         [](CPU *cpu) {
                             cpu->store_memory_indirect(0xFF00 + cpu->get_registers()[REGISTER_C_INDEX], REGISTER_A_INDEX);
                         });

    cpu->register_opcode("LDH A (a8)",
                         [](uint16_t opcode) { return opcode == 0xF0; },
                         [](CPU *cpu) {
                             cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->fetch_next_byte());
                         });

    cpu->register_opcode("LD A (C)",
                         [](uint16_t opcode) { return opcode == 0xF2; },
                         [](CPU *cpu) {
                             cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->get_registers()[REGISTER_C_INDEX]);
                         });

    cpu->register_opcode("LD A (a16)",
                         [](uint16_t opcode) { return opcode == 0xFA; },
                         [](CPU *cpu) {
                             uint16_t address = cpu->fetch_next_word();
                             cpu->load_memory_indirect(REGISTER_A_INDEX, address);
                         });
}