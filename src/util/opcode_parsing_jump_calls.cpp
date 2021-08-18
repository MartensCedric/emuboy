//
// Created by cedric on 2021-08-17.
//

#include <memory/memory_management_unit.h>
#include <cpu/CPU.h>
#include <util/opcode_parsing_math.h>

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