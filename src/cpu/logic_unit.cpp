//
// Created by cedric on 2021-07-24.
//

#include <cpu/logic_unit.h>

LogicUnit::LogicUnit(CPU *cpu) {
    this->cpu = cpu;
}

void LogicUnit::compare_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value - cpu->get_registers()[register_y];
    this->set_compare_flags(new_value, original_value);
}

void LogicUnit::logic_or_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value | cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_or_flags(new_value, original_value);
}

void LogicUnit::logic_or_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value | immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_or_flags(new_value, original_value);
}

void LogicUnit::logic_and_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value & cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_and_flags(new_value, original_value);
}

void LogicUnit::logic_and_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value & immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_and_flags(new_value, original_value);
}

void LogicUnit::logic_xor_registers_8bit(uint8_t register_x, uint8_t register_y) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value ^ cpu->get_registers()[register_y];
    cpu->load_register_immediate(register_x, new_value);
    this->set_xor_flags(new_value, original_value);
}

void LogicUnit::logic_xor_immediate_8bit(uint8_t register_x, uint8_t immediate_value) {
    const uint8_t original_value = cpu->get_registers()[register_x];
    const uint8_t new_value = original_value ^ immediate_value;
    cpu->load_register_immediate(register_x, new_value);
    this->set_xor_flags(new_value, original_value);
}

LogicUnit::~LogicUnit() {

}

