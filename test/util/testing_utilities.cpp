//
// Created by cedric on 2021-06-20.
//

#include "cpu/CPU.h"
#include <initializer_list>
#include <algorithm>

void set_next_opcode(CPU* cpu, std::initializer_list<uint8_t> opcode)
{
    const uint16_t initial_address = cpu->get_program_counter();
    for(std::initializer_list<uint8_t>::iterator it = opcode.begin(); it != opcode.end(); it++)
    {
        const uint16_t address = cpu->get_program_counter();
        cpu->store_memory_immediate(address, *it);
        cpu->increment_pc();
    }

    cpu->jump_to_address(initial_address);
}

void run_next_opcode(CPU* cpu, std::initializer_list<uint8_t> opcode)
{
    set_next_opcode(cpu, opcode);
    cpu->fetch_cycle();
}

