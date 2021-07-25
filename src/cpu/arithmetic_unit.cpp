//
// Created by cedric on 2021-07-24.
//

#include "cpu/arithmetic_unit.h"

ArithmeticUnit::ArithmeticUnit(CPU *cpu) {
    this->cpu = cpu;
}

void ArithmeticUnit::add_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::add_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::add_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + cpu->memory[address];
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::add_memory_immediate_8bit(uint16_t address, uint8_t immediate_value) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value + immediate_value;
    cpu->store_memory_immediate(address, new_value);
    this->set_addition_flags(new_value, original_value);
}

void ArithmeticUnit::sub_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::sub_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::sub_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - cpu->memory[address];
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value);
}

void ArithmeticUnit::sub_memory_immediate_8bit(uint16_t address, uint8_t immediate_value) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value - immediate_value;
    cpu->store_memory_immediate(address, new_value);
    this->set_subtraction_flags(new_value, original_value);
}

void ArithmeticUnit::increment_register_8bit(uint8_t register_x) {
    this->add_register_immediate_8bit(register_x, 1);
}

void ArithmeticUnit::increment_indirect_8bit(uint16_t address) {
    this->add_memory_immediate_8bit(address, 1);
}

void ArithmeticUnit::decrement_register_8bit(uint8_t register_x) {
    this->sub_register_immediate_8bit(register_x, 1);
}

void ArithmeticUnit::decrement_indirect_8bit(uint16_t address) {
    this->sub_memory_immediate_8bit(address, 1);
}

ArithmeticUnit::~ArithmeticUnit() {

}