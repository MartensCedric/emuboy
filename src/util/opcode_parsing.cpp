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

void call_misc(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

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
            cpu->fetch_next_byte();
            call_8bit_rotation_shifts(cpu);
            break;
        case 0xF3:
            cpu->disable_interrupts();
            break;
        case 0xFB:
            cpu->enable_interrupts();
            break;
        default:
            throw std::runtime_error("Cannot find misc instruction!");
    }
}

void call_jump_calls(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(first_byte == 0x18)
    {
       cpu->jump_to_address(cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
    }
    else if(first_byte == 0x20)
    {
        if(!cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
    }
    else if(first_byte == 0x28)
    {
        if(cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
    }
    else if(first_byte == 0x30)
    {
        if(!cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
    }
    else if(first_byte == 0x38)
    {
        if(cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->get_program_counter() + static_cast<int8_t>(cpu->fetch_next_byte()));
    }
    else if(byte_in_range_vertical(first_byte, 0xC7, 0xF7) ||
        byte_in_range_vertical(first_byte, 0xCF, 0xFF))
    {
        cpu->push(cpu->get_program_counter());
        cpu->jump_to_address(first_byte - 0xC7);
    }
    else if(first_byte == 0xC0)
    {
        if(!cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xC2)
    {
        if(!cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->fetch_next_word());
    }
    else if(first_byte == 0xC3)
    {
        cpu->jump_to_address(cpu->fetch_next_word());
    }
    else if(first_byte == 0xC4)
    {
        if(!cpu->is_zero_flag_on())
        {
            // todo: refactor into call() function
            cpu->push(cpu->get_program_counter() + 3);
            cpu->jump_to_address(cpu->fetch_next_word());
        }
    }
    else if(first_byte == 0xC8)
    {
        if(cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xC9)
    {
        cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xCA)
    {
        if(cpu->is_zero_flag_on())
            cpu->jump_to_address(cpu->fetch_next_word());
    }
    else if(first_byte == 0xCE)
    {
        cpu->get_arithmetic_unit()->add_carry_registers_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xD0)
    {
        if(!cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xD2)
    {
        if(!cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->fetch_next_word());
    }
    else if(first_byte == 0xD4)
    {
        if(!cpu->is_carry_flag_on())
        {
            // todo: refactor into call() function
            cpu->push(cpu->get_program_counter() + 3);
            cpu->jump_to_address(cpu->fetch_next_word());
        }
    }
    else if(first_byte == 0xD8)
    {
        if(cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->pop());
    }
    else if(first_byte == 0xDA)
    {
        if(cpu->is_carry_flag_on())
            cpu->jump_to_address(cpu->fetch_next_word());
    }
    else if(first_byte == 0xD9)
    {
        cpu->jump_to_address(cpu->pop());
        cpu->enable_interrupts();
    }
    else if(first_byte == 0xDE)
    {
        cpu->get_arithmetic_unit()->sub_carry_registers_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xE9)
    {
        cpu->jump_to_address(cpu->get_word_memory_indirect(cpu->get_16bit_register(REGISTER_HL_INDEX)));
    }
    else if(first_byte == 0xEE)
    {
        cpu->get_logic_unit()->logic_xor_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xFE)
    {
        cpu->get_logic_unit()->compare_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
}
void call_16bit_lsm(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(byte_in_range_vertical(first_byte, 0x01, 0x31))
    {
        uint16_t data = cpu->fetch_next_word();
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
    else if(first_byte == 0xF9)
    {
        cpu->load_16bit_register_immediate(REGISTER_SP_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
}

void call_8bit_arithmetic(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(byte_in_range(first_byte, 0x80, 0x85))
    {
        cpu->get_arithmetic_unit()->add_registers_8bit(REGISTER_A_INDEX, first_byte & 0xF);
    }
    else if(first_byte == 0x86)
    {
        cpu->get_arithmetic_unit()->add_register_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0x87)
    {
        cpu->get_arithmetic_unit()->add_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    }
    else if(first_byte == 0x96)
    {
        cpu->get_logic_unit()->logic_and_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0x97)
    {
        cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    }
    else if(first_byte == 0xA6)
    {
        cpu->get_logic_unit()->logic_and_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0xA7)
    {
        cpu->get_logic_unit()->logic_and_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    }
    else if(first_byte == 0xB6)
    {
        cpu->get_logic_unit()->logic_or_indirect_8bit(REGISTER_A_INDEX, cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0xB7)
    {
        cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, REGISTER_A_INDEX);
    }
    else if(first_byte == 0x2F)
    {
        cpu->get_logic_unit()->complement_register(REGISTER_A_INDEX);
    }
    else if(byte_in_range(first_byte, 0x90, 0x95))
    {
        cpu->get_arithmetic_unit()->sub_registers_8bit(REGISTER_A_INDEX, first_byte & 0xF);
    }
    else if(byte_in_range(first_byte, 0xA0, 0xA5))
    {
        uint8_t original_value = cpu->get_registers()[REGISTER_A_INDEX];
        uint8_t value_to_and = cpu->get_registers()[first_byte & 0xF];

        uint8_t new_value = original_value & value_to_and;
        cpu->load_register_immediate(REGISTER_A_INDEX, new_value);
    }
    else if(byte_in_range(first_byte, 0xA8, 0xAD))
    {
        cpu->get_logic_unit()->logic_or_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }
    else if(byte_in_range(first_byte, 0xB0, 0xB5))
    {
        cpu->get_logic_unit()->logic_xor_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }
    else if(byte_in_range(first_byte, 0xB8, 0xBD))
    {
        cpu->get_logic_unit()->compare_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }
    else if(first_byte == 0xC6)
    {
        cpu->get_arithmetic_unit()->add_register_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xD6)
    {
        cpu->get_arithmetic_unit()->sub_register_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xE6)
    {
        cpu->get_logic_unit()->logic_and_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(first_byte == 0xF6)
    {
        cpu->get_logic_unit()->logic_or_immediate_8bit(REGISTER_A_INDEX, cpu->fetch_next_byte());
    }
    else if(byte_in_range_vertical(first_byte, 0x04, 0x24))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
    }
    else if(byte_in_range_vertical(first_byte, 0x05, 0x25))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
    }
    else if(byte_in_range_vertical(first_byte, 0x0C, 0x3C))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->increment_register_8bit(reg_x);
    }
    else if(byte_in_range_vertical(first_byte, 0x0D, 0x3D))
    {
        const uint8_t reg_x = (((first_byte & 0xF0) >> 4) * 2) + ((first_byte & 0x08) >> 3);
        cpu->get_arithmetic_unit()->decrement_register_8bit(reg_x);
    }
    else if(first_byte == 0x34)
    {
        cpu->get_arithmetic_unit()->increment_indirect_8bit(cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0x35)
    {
        cpu->get_arithmetic_unit()->decrement_indirect_8bit(cpu->get_16bit_register(REGISTER_HL_INDEX));
    }
    else if(first_byte == 0x37)
    {
        cpu->get_logic_unit()->set_carry_flag();
    }
    else if(first_byte == 0x3F)
    {
        cpu->get_logic_unit()->complement_carry_flag();
    }
    else if(byte_in_range(first_byte, 0x88, 0x8D))
    {
        cpu->get_arithmetic_unit()->add_carry_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }
    else if(byte_in_range(first_byte, 0x98, 0x9D))
    {
        cpu->get_arithmetic_unit()->add_carry_registers_8bit(REGISTER_A_INDEX, (first_byte - 8) & 0xF);
    }

}
void call_16bit_arithmetic(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(byte_in_range_vertical(first_byte, 0x03, 0x33))
    {
        uint8_t reg_x = ((first_byte & 0xF0) >> 4) + 1;
        uint16_t value = cpu->get_16bit_register(reg_x);
        value++;
        cpu->load_16bit_register_immediate(reg_x, value);
    }
    else if(byte_in_range_vertical(first_byte, 0x0B, 0x3B))
    {
        uint8_t reg_x = ((first_byte & 0xF0) >> 4) + 1;
        uint16_t value = cpu->get_16bit_register(reg_x);
        value--;
        cpu->load_16bit_register_immediate(reg_x, value);
    }
    else if(byte_in_range_vertical(first_byte, 0x09, 0x39))
    {
        uint8_t reg_x = ((first_byte & 0xF0) >> 4) + 1;
        uint16_t value_added = cpu->get_16bit_register(reg_x);
        uint16_t base_value = cpu->get_16bit_register(REGISTER_HL_INDEX);
        uint16_t final_value = base_value + value_added;
//        cpu->setSubtractFlag(false);
//        cpu->setCarryFlag(final_value < base_value);
//        cpu->setHalfCarryFlag(((base_value & 0xF) + (final_value & 0xF)) < (base_value & 0xF));
        cpu->load_16bit_register_immediate(REGISTER_HL_INDEX, final_value);
    }
    else if(first_byte == 0xE8)
    {
        uint16_t base_value = cpu->get_16bit_register(REGISTER_SP_INDEX);
        uint16_t value_added = static_cast<uint16_t>(cpu->fetch_next_byte());
        uint16_t final_value = base_value + value_added;
        cpu->load_16bit_register_immediate(REGISTER_SP_INDEX, final_value);
//        cpu->setZeroFlag(false);
//        cpu->setSubtractFlag(false);
//        cpu->setCarryFlag(final_value < base_value);
//        cpu->setHalfCarryFlag(((base_value & 0xF) + (final_value & 0xF)) < (base_value & 0xF));
    }
}

void call_8bit_rotation_shifts(CPU* cpu)
{
    uint8_t first_byte = cpu->fetch_byte();

    if(first_byte == 0x07)
    {
        // todo: RLCA
    }
    else if(first_byte == 0x17)
    {
        // todo: RLA
    }
    else if(first_byte == 0xCB)
    {
        uint8_t second_byte = cpu->fetch_next_byte();
        if(byte_in_range(second_byte, 0x20, 0x25))
        {

        }
        else if(byte_in_range_matrix(second_byte, 0x80,0xB3))
        {
            uint8_t bit_to_test = (((second_byte & 0xF0) >> 8) - 0x0C) * 2;
            uint8_t register_x = second_byte & 0xF;
            cpu->get_shifting_unit()->test_bit_register(bit_to_test, register_x);
        }
        else if(byte_in_range_matrix(second_byte, 0x80,0xB3))
        {
            uint8_t bit_to_reset = (((second_byte & 0xF0) >> 8) - 0x0C) * 2;
            uint8_t register_x = second_byte & 0xF;
            cpu->get_shifting_unit()->reset_bit_register(bit_to_reset, register_x);
        }
        else if(byte_in_range_matrix(second_byte, 0xC0,0xF3))
        {
            uint8_t bit_to_set = (((second_byte & 0xF0) >> 8) - 0x0C) * 2;
            uint8_t register_x = second_byte & 0xF;
            cpu->get_shifting_unit()->set_bit_register(bit_to_set, register_x);
        }
    }
}