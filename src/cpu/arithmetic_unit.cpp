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
    this->set_addition_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::add_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::add_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + cpu->memory[address];
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::add_memory_immediate_8bit(uint16_t address, uint8_t immediate_value) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value + immediate_value;
    cpu->store_memory_immediate(address, new_value);
    this->set_addition_flags(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::add_carry_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    const uint8_t original_value = cpu->registers[register_x];
    const uint8_t value_to_add = immediate_value + carry_bit;

    this->add_register_immediate_8bit(register_x, value_to_add);

    const uint8_t new_value = original_value + value_to_add;
    this->set_addition_flags(new_value, original_value, FLAGS_ALL);
}


void ArithmeticUnit::add_carry_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    const uint8_t original_value = cpu->registers[register_x];
    const uint8_t value_to_add = this->cpu->memory[address] + carry_bit;

    this->add_register_immediate_8bit(register_x, value_to_add);

    const uint8_t new_value = original_value + value_to_add;
    this->set_addition_flags(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::add_carry_register_8bit(uint8_t register_x, uint8_t register_y) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    const uint8_t original_value = cpu->registers[register_x];
    const uint8_t value_to_add = this->cpu->registers[register_y] + carry_bit;

    this->add_register_immediate_8bit(register_x, value_to_add);

    const uint8_t new_value = original_value + value_to_add;
    this->set_addition_flags(new_value, original_value, FLAGS_ALL);
}


void ArithmeticUnit::sub_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::sub_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::sub_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - cpu->memory[address];
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::sub_memory_immediate_8bit(uint16_t address, uint8_t immediate_value) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value - immediate_value;
    cpu->store_memory_immediate(address, new_value);
    this->set_subtraction_flags(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::sub_carry_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    this->sub_register_immediate_8bit(register_x, immediate_value + carry_bit);
}


void ArithmeticUnit::sub_carry_register_indirect_8bit(uint8_t register_x, uint16_t address) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    const uint8_t original_value = cpu->registers[register_x];
    const uint8_t value_to_sub = this->cpu->memory[address] + carry_bit;

    this->sub_register_immediate_8bit(register_x, value_to_sub);

    const uint8_t new_value = original_value + value_to_sub;
    this->set_subtraction_flags(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::sub_carry_register_8bit(uint8_t register_x, uint8_t immediate_value) {
    uint8_t carry_bit = cpu->is_carry_flag_on() ? 1 : 0;
    const uint8_t original_value = cpu->registers[register_x];
    const uint8_t value_to_sub = immediate_value + carry_bit;

    this->sub_register_immediate_8bit(register_x, value_to_sub);

    const uint8_t new_value = original_value + value_to_sub;
    this->set_subtraction_flags(new_value, original_value, FLAGS_ALL);
}

void ArithmeticUnit::increment_register_8bit(uint8_t register_x) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value + 1;
    cpu->load_register_immediate(register_x, new_value);
    this->set_addition_flags<uint8_t>(new_value, original_value, FLAGS_NO_CARRY);
}

void ArithmeticUnit::increment_indirect_8bit(uint16_t address) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value + 1;
    cpu->store_memory_immediate(address, new_value);
    this->set_addition_flags(new_value, original_value, FLAGS_NO_CARRY);
}

void ArithmeticUnit::decrement_register_8bit(uint8_t register_x) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - 1;
    cpu->load_register_immediate(register_x, new_value);
    this->set_subtraction_flags<uint8_t>(new_value, original_value, FLAGS_NO_CARRY);
}

void ArithmeticUnit::decrement_indirect_8bit(uint16_t address) {
    const uint8_t original_value = cpu->memory[address];
    const uint8_t new_value = original_value - 1;
    cpu->store_memory_immediate(address, new_value);
    this->set_subtraction_flags(new_value, original_value, FLAGS_NO_CARRY);
}

ArithmeticUnit::~ArithmeticUnit() {

}
