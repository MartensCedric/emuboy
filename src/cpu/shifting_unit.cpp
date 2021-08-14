//
// Created by cedric on 2021-08-11.
//

#include "cpu/shifting_unit.h"

ShiftingUnit::ShiftingUnit(CPU *cpu) {
    this->cpu = cpu;
}

void ShiftingUnit::set_bit_register(uint8_t bit, uint8_t register_x) {
    uint8_t value = this->cpu->get_registers()[register_x];
    value |= (1 << bit);
    this->cpu->load_register_immediate(register_x, value);
}

void ShiftingUnit::reset_bit_register(uint8_t bit, uint8_t register_x) {
    uint8_t value = this->cpu->get_registers()[register_x];
    value &= ~(1 << bit);
    this->cpu->load_register_immediate(register_x, value);
}

void ShiftingUnit::test_bit_register(uint8_t bit, uint8_t register_x) {

    this->cpu->set_zero_flag(!(this->cpu->get_registers()[register_x] & (1 << bit)));
    this->cpu->set_half_carry_flag(true);
    this->cpu->set_subtract_flag(false);
    this->cpu->set_half_carry_flag(true);
}

ShiftingUnit::~ShiftingUnit() {

}

