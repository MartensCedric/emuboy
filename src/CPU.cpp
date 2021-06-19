//
// Created by cedric on 2021-06-16.
//

#include "CPU.h"
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <ios>
#include <sstream>
#include "safety.h"

CPU::CPU() {
    memset(this->memory, 0, NUM_MEMORY_BYTES);
    memset(this->registers, 0, NUM_REGISTERS);
    this->stack_pointer = NUM_MEMORY_BYTES - 1;
    this->program_counter = 0x100;
}

uint16_t CPU::get_program_counter() const {
    return this->program_counter;
}

uint16_t CPU::get_stack_pointer() const {
    return this->stack_pointer;
}

uint8_t CPU::fetch() const{
    return this->memory[this->get_program_counter()];
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

void CPU::jump_to_address(uint16_t address) {
    this->program_counter = address;
}

void CPU::increment_pc() {
    this->increment_pc(1);
}

void CPU::increment_pc(uint16_t bytes_to_increment) {
    this->program_counter += bytes_to_increment;
}

void CPU::load_immediate(uint8_t reg_x, uint8_t immediate_value) {
    validate_argument<uint8_t>(reg_x, 0x8);
    this->registers[reg_x] = immediate_value;
}

void CPU::load_register_indirect(uint8_t reg_x, uint8_t reg_y) {
    validate_argument<uint8_t>(reg_x, 0x8);
    this->registers[reg_x] = this->registers[reg_y];
}

void CPU::load_memory_indirect(uint8_t reg_x, uint16_t memory_address) {
    validate_argument<uint8_t>(reg_x, 0x8);
    this->registers[reg_x] = this->memory[memory_address];
}

void CPU::store_memory_indirect(uint16_t memory_address, uint8_t reg_x) {
    validate_argument<uint8_t>(reg_x, 0x8);
    this->memory[memory_address] = this->registers[reg_x];
}
