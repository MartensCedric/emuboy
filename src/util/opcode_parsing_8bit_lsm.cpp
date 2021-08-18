//
// Created by cedric on 2021-08-17.
//


#include <memory/memory_management_unit.h>
#include <cpu/CPU.h>
#include <util/opcode_parsing_math.h>

void call_8bit_lsm(CPU* cpu) {
    uint8_t first_byte = cpu->fetch_byte();

    if (byte_in_range_vertical(first_byte, 0x02, 0x12)) {
        const uint8_t reg_x = 1 + ((first_byte & 0xF0) >> 4);
        cpu->store_memory_indirect(cpu->get_16bit_register(reg_x), REGISTER_A_INDEX);
    }
    else if(byte_in_range_vertical(first_byte, 0x2A, 0x3A))
    {
        uint16_t memory_address = cpu->get_16bit_register(REGISTER_HL_INDEX);
        cpu->load_memory_indirect(REGISTER_A_INDEX, memory_address);

        if(first_byte == 0x2A)
            memory_address++;
        else
            memory_address--;

        cpu->load_register_immediate(REGISTER_H_INDEX, memory_address & 0xF0);
        cpu->load_register_immediate(REGISTER_L_INDEX, memory_address & 0x0F);
    }
    else if(byte_in_range_vertical(first_byte, 0x22, 0x32))
    {
        uint16_t memory_address = cpu->get_16bit_register(REGISTER_HL_INDEX);
        cpu->store_memory_indirect(memory_address, REGISTER_A_INDEX);

        if(first_byte == 0x22)
            memory_address++;
        else
            memory_address--;

        cpu->load_register_immediate(REGISTER_H_INDEX, memory_address & 0xF0);
        cpu->load_register_immediate(REGISTER_L_INDEX, memory_address & 0x0F);
    }
    else if(byte_in_range_vertical(first_byte, 0x0A, 0x1A))
    {
        const uint8_t reg_x = first_byte == 0x0A ? REGISTER_BC_INDEX : REGISTER_DE_INDEX;
        cpu->load_memory_indirect(REGISTER_A_INDEX, cpu->get_16bit_register(reg_x));
    }
    else if(byte_in_range_matrix(first_byte, 0x40, 0x65))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        const uint8_t reg_y = first_byte & 0xF;
        cpu->load_register_indirect(reg_x, reg_y);
    }
    else if(byte_in_range_matrix(first_byte, 0x48, 0x6D))
    {
        const uint8_t reg_x = 1 + (((first_byte & 0xF0) >> 4) - 4) * 2;
        const uint8_t reg_y = (first_byte & 0xF) - 8;
        cpu->load_register_indirect(reg_x, reg_y);
    }
    else if(byte_in_range_vertical(first_byte, 0x46, 0x66))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_memory_indirect(reg_x, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(byte_in_range_vertical(first_byte, 0x47, 0x67))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_register_indirect(reg_x, REGISTER_A_INDEX);
    }
    else if(byte_in_range_vertical(first_byte, 0x4E, 0x7E))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_memory_indirect(reg_x, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(byte_in_range_vertical(first_byte, 0x4F, 0x7F))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) - 4) * 2;
        cpu->load_memory_indirect(reg_x, REGISTER_A_INDEX);
    }
    else if(byte_in_range_vertical(first_byte, 0x06, 0x26) ||
            byte_in_range_vertical(first_byte, 0x0E, 0x3E))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->load_register_immediate(reg_x, cpu->fetch_next_byte());
    }
    else if(byte_in_range(first_byte, 0x70, 0x75))
    {
        const uint8_t reg_x = first_byte & 0xF;
        cpu->store_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX), reg_x);
    }
    else if(first_byte == 0x77)
    {
        cpu->store_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX), REGISTER_A_INDEX);
    }
    else if(first_byte == 0x36)
    {
        cpu->store_memory_immediate(cpu->get_16bit_register(REGISTER_HL_INDEX), cpu->fetch_next_byte());
    }
    else if(byte_in_range(first_byte, 0x78, 0x7D))
    {
        cpu->load_register_indirect(REGISTER_A_INDEX, first_byte - 0x78);
    }
    else if(first_byte == 0xE0) {
        cpu->store_memory_indirect(0xFF00 + cpu->fetch_next_byte(), REGISTER_A_INDEX);
    }
    else if(first_byte == 0xEA)
    {
        uint16_t address = cpu->fetch_next_word();
        cpu->store_memory_indirect(address, REGISTER_A_INDEX);
    }
    else if(first_byte == 0xE2)
    {
        cpu->store_memory_indirect(0xFF00 + cpu->get_registers()[REGISTER_C_INDEX], REGISTER_A_INDEX);
    }
    else if(first_byte == 0xF0)
    {
        cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->fetch_next_byte());
    }
    else if(first_byte == 0xF2)
    {
        cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->get_registers()[REGISTER_C_INDEX]);
    }
    else if(first_byte == 0xFA)
    {
        uint16_t address = cpu->fetch_next_word();
        cpu->load_memory_indirect(REGISTER_A_INDEX, address);
    }
}