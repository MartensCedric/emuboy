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
    }
    else if(next_is_8bit_arithmetic(this))
    {
        call_8bit_arithmetic(this);
    }
    else
    {
        throw std::runtime_error("Could not find opcode!");
    }
}


CPU::~CPU() {
    delete[] memory;
    delete[] registers;
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

void CPU::load_register_immediate(uint8_t reg_x, uint8_t value) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->registers[reg_x] = value;
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
    return this->registers;
}

uint16_t CPU::get_16bit_register(uint8_t index) const {
    switch (index) {
        case REGISTER_AF_INDEX:
            return (((uint16_t)this->registers[REGISTER_A_INDEX]) << 8) + ((uint16_t)this->registers[REGISTER_F_INDEX]);
        case REGISTER_BC_INDEX:
            return (((uint16_t)this->registers[REGISTER_B_INDEX]) << 8) + ((uint16_t)this->registers[REGISTER_C_INDEX]);
        case REGISTER_DE_INDEX:
            return (((uint16_t)this->registers[REGISTER_D_INDEX]) << 8) + ((uint16_t)this->registers[REGISTER_E_INDEX]);
        case REGISTER_HL_INDEX:
            return (((uint16_t)this->registers[REGISTER_H_INDEX]) << 8) + ((uint16_t)this->registers[REGISTER_L_INDEX]);
        default:
            throw std::runtime_error("16bit register index out of bounds!");
    }
}

void CPU::setZeroFlag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0x7F;
    this->registers[REGISTER_F_INDEX] += (int(isOn) << 7);
}

void CPU::setSubtractFlag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xBF;
    this->registers[REGISTER_F_INDEX] += (int(isOn) << 6);
}

void CPU::setCarryFlag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xDF;
    this->registers[REGISTER_F_INDEX] += (int(isOn) << 5);
}

void CPU::setHalfCarryFlag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xEF;
    this->registers[REGISTER_F_INDEX] += (int(isOn) << 4);
}



