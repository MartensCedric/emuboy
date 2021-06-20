//
// Created by cedric on 2021-06-16.
//

#include "CPU.h"
#include <cstring>
#include <cstdlib>
#include <stdexcept>
#include <ios>
#include <sstream>
#include <util/opcode_parsing.h>
#include "safety.h"
#include "opcode_parsing_categories.h"

CPU::CPU() {
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

uint8_t CPU::fetch_next() {
    this->increment_pc();
    return this->fetch();
}

void CPU::fetch_cycle() {
    this->process_opcode();
}

void CPU::process_opcode() {
    if(next_is_8bit_lsm(this))
    {
        call_8bit_lsm(this);
        return;
    }

    throw std::runtime_error("Could not find opcode!");
}


CPU::~CPU() {

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
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->registers[reg_x] = immediate_value;
}

void CPU::load_register_indirect(uint8_t reg_x, uint8_t reg_y) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    validate_leq_than<uint8_t>(reg_y, 0x08);
    this->registers[reg_x] = this->registers[reg_y];
}

void CPU::load_memory_indirect(uint8_t reg_x, uint16_t memory_address) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->registers[reg_x] = this->memory[memory_address];
}

void CPU::store_memory_indirect(uint16_t memory_address, uint8_t reg_x) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->memory[memory_address] = this->registers[reg_x];
}

void CPU::store_memory_immediate(uint16_t memory_address, uint8_t value) {
    this->memory[memory_address] = value;
}

const uint8_t* CPU::get_registers() const {
    return this->registers.get();
}

