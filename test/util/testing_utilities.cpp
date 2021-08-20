//
// Created by cedric on 2021-06-20.
//

#include "cpu/CPU.h"
#include <initializer_list>
#include <algorithm>
#include "cpu/flags.h"

void set_next_opcode(CPU *cpu, std::initializer_list<uint8_t> opcode) {
    const uint16_t initial_address = cpu->get_program_counter();
    for (std::initializer_list<uint8_t>::iterator it = opcode.begin(); it != opcode.end(); it++) {
        const uint16_t address = cpu->get_program_counter();
        cpu->store_memory_immediate(address, *it);
        cpu->increment_pc();
    }

    cpu->jump_to_address(initial_address);
}

void run_next_opcode(CPU *cpu, std::initializer_list<uint8_t> opcode) {
    set_next_opcode(cpu, opcode);
    cpu->fetch_cycle();
}

void set_flags(CPU *cpu, flags flags) {
    uint8_t flags_to_set = 0;
    flags_to_set |= flags.zero_flag ? 0x80 : 0;
    flags_to_set |= flags.subtract_flag ? 0x40 : 0;
    flags_to_set |= flags.half_carry_flag ? 0x20 : 0;
    flags_to_set |= flags.carry_flag ? 0x10 : 0;
    cpu->load_register_immediate(REGISTER_F_INDEX, flags_to_set);
}
