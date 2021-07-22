//
// Created by cedric on 2021-06-19.
//

#include <stdexcept>
#include "opcode_parsing.h"
#include "opcode_parsing_math.h"

/**
 * To understand what is going in this file, it is critical that
 * the reader follows with this table:
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

void call_8bit_lsm(CPU* cpu) {
    uint8_t first_byte = cpu->fetch();

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
        cpu->load_register_immediate(reg_x, cpu->fetch_next());
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
        cpu->store_memory_immediate(cpu->get_16bit_register(REGISTER_HL_INDEX), cpu->fetch_next());
    }
    else if(byte_in_range(first_byte, 0x78, 0x7D))
    {
        cpu->load_register_indirect(REGISTER_A_INDEX, first_byte - 0x78);
    }
    else if(first_byte == 0xE0) {
        cpu->store_memory_indirect(0xFF00 + cpu->fetch_next(), REGISTER_A_INDEX);
    }
    else if(first_byte == 0xEA)
    {
        uint16_t address = cpu->fetch_next();
        address += (static_cast<uint16_t>(cpu->fetch_next()) << 8);
        cpu->store_memory_indirect(address, REGISTER_A_INDEX);
    }
    else if(first_byte == 0xE2)
    {
        cpu->store_memory_indirect(0xFF00 + cpu->get_registers()[REGISTER_C_INDEX], REGISTER_A_INDEX);
    }
    else if(first_byte == 0xF0)
    {
        cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->fetch_next());
    }
    else if(first_byte == 0xF2)
    {
        cpu->load_memory_indirect(REGISTER_A_INDEX, 0xFF00 + cpu->get_registers()[REGISTER_C_INDEX]);
    }
    else if(first_byte == 0xFA)
    {
        uint16_t address = cpu->fetch_next();
        address += (static_cast<uint16_t>(cpu->fetch_next())) << 8;
        cpu->load_memory_indirect(REGISTER_A_INDEX, address);
    }
}

void call_misc(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    switch (first_byte) {
        case 0x00:
            // nop
            break;
        case 0x10:
            cpu->stop();
            break;
        case 0x76:
            cpu->halt();
            break;
        case 0xCB:
            cpu->fetch_next();
            call_8bit_rotation_shifts(cpu);
            break;
        case 0xF3:
            cpu->disable_interrupts();
        case 0xFB:
            cpu->enable_interrupts();
        default:
            throw std::runtime_error("Cannot find misc instruction!");
    }
}

void call_jump_calls(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    if(byte_in_range_vertical(first_byte, 0xC7, 0xF7) ||
        byte_in_range_vertical(first_byte, 0xCF, 0xFF))
    {
        cpu->push(cpu->get_program_counter());
        cpu->jump_to_address(first_byte - 0xC8);
    }
    else if(first_byte == 0xC0)
    {
        if(!cpu->isZeroFlagOn())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xC8)
    {
        if(cpu->isZeroFlagOn())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xC9)
    {
        cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xD0)
    {
        if(!cpu->isCarryFlagOn())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xD8)
    {
        if(cpu->isCarryFlagOn())
            cpu->jump_to_address(cpu->pop());
    }
}
void call_16bit_lsm(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    if(byte_in_range_vertical(first_byte, 0x01, 0x31))
    {
        uint16_t data = (static_cast<uint16_t>(cpu->fetch_next())) << 8;
        data |= cpu->fetch_next();

        cpu->load_16bit_register_immediate(1 + (first_byte >> 4), data);
    }
    else if(byte_in_range_vertical(first_byte, 0xC1, 0xF1))
    {
        uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
        cpu->load_16bit_register_immediate(reg_x, cpu->pop());
    }
    else if(byte_in_range_vertical(first_byte, 0xC5, 0xF5))
    {
        uint8_t reg_x = (((first_byte & 0xF0) >> 8) - 11) % 4;
        cpu->push(cpu->get_16bit_register(reg_x));
    }
}

void call_8bit_arithmetic(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    if(byte_in_range(first_byte, 0x80, 0x85))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_add = cpu->get_registers()[first_byte & 0xF];

        uint8_t new_value = original_value + value_to_add;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(false);
        cpu->setCarryFlag(new_value < original_value);
        cpu->setHalfCarryFlag(((original_value & 0xF) + (new_value & 0xF)) < (original_value & 0xF));
    }
    else if(byte_in_range(first_byte, 0x90, 0x95))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_subtract = cpu->get_registers()[first_byte & 0xF];

        uint8_t new_value = original_value - value_to_subtract;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(true);
        cpu->setCarryFlag(new_value > original_value);
        cpu->setHalfCarryFlag(((original_value & 0xF) - (new_value & 0xF)) > (original_value & 0xF));
    }
    else if(byte_in_range(first_byte, 0xA0, 0xA5))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_and = cpu->get_registers()[first_byte & 0xF];

        uint8_t new_value = original_value & value_to_and;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(false);
        cpu->setCarryFlag(true);
        cpu->setHalfCarryFlag(false);
    }
    else if(byte_in_range(first_byte, 0xA8, 0xAD))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_xor = cpu->get_registers()[(first_byte - 8) & 0xF];

        uint8_t new_value = original_value ^ value_to_xor;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(false);
        cpu->setCarryFlag(false);
        cpu->setHalfCarryFlag(false);
    }
    else if(byte_in_range(first_byte, 0xB0, 0xB5))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_or = cpu->get_registers()[first_byte & 0xF];

        uint8_t new_value = original_value | value_to_or;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(false);
        cpu->setCarryFlag(false);
        cpu->setHalfCarryFlag(false);
    }
    else if(byte_in_range(first_byte, 0xB8, 0xBD))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_subtract = cpu->get_registers()[(first_byte - 8) & 0xF];

        uint8_t new_value = original_value - value_to_subtract;

        cpu->setZeroFlag(new_value == 0);
        cpu->setSubtractFlag(true);
        cpu->setCarryFlag(new_value > original_value);
        cpu->setHalfCarryFlag(((original_value & 0xF) - (new_value & 0xF)) > (original_value & 0xF));
    }

}
void call_16bit_arithmetic(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch();

    if(byte_in_range_vertical(first_byte, 0x03, 0x33))
    {
        uint8_t reg_x = ((first_byte & 0xF0) >> 4) + 1;
        uint16_t value = cpu->get_16bit_register(reg_x);
        value++;
        cpu->load_16bit_register_immediate(reg_x, value);
    }
}

void call_8bit_rotation_shifts(CPU* cpu)
{

}