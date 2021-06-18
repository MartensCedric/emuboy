//
// Created by cedric on 2021-06-16.
//

#include "CPU.h"
#include <stdio.h>
#include <cstring>
#include <malloc.h>
#include <cstdlib>
#include <stdexcept>
#include <ios>
#include <sstream>

CPU::CPU() {
    memset(this->memory, 0, NUM_MEMORY_BYTES);
    memset(this->registers, 0, NUM_REGISTERS);
    this->stack_pointer = NUM_MEMORY_BYTES - 1;
    this->program_counter = 0x100;
}

uint16_t CPU::get_program_counter() {
    return this->program_counter;
}

uint16_t CPU::get_stack_pointer() {
    return this->stack_pointer;
}

void CPU::fetch_cycle() {

}

void CPU::process_opcode() {

    const uint8_t first_byte = this->memory[this->program_counter];
    switch (first_byte) {
        case 0xCE:
            break;
        default:
            std::stringstream ss("Could not find opcode: 0x");
            ss << std::hex << first_byte;
            throw std::runtime_error(ss.str());
    }
}


CPU::~CPU() {
    free(this->memory);
    free(this->registers);
}