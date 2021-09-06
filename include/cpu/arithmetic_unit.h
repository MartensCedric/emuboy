//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_ARITHMETICUNIT_H
#define EMUBOY_ARITHMETICUNIT_H

#include <cmath>
#include "cpu/CPU.h"
#include "cpu/flags.h"
#include "memory/memory_management_unit.h"


class ArithmeticUnit {
private:
    CPU *cpu;

    template<typename T>
    void set_addition_flags(T new_value, T original_value, flags options) {
        if (options.zero_flag)
            cpu->set_zero_flag(new_value == 0);

        if (options.subtract_flag)
            cpu->set_subtract_flag(false);

        if (options.half_carry_flag) {
            size_t bits_for_half_the_type = sizeof(T) * 4;
            T lower_mask = std::pow(2, bits_for_half_the_type) - 1;
            T carry_mask = 1 << bits_for_half_the_type;

            cpu->set_half_carry_flag(
                    (((new_value - original_value) & lower_mask) + (original_value & lower_mask)) & carry_mask);
        }

        if (options.carry_flag)
            cpu->set_carry_flag(new_value < original_value);
    }

    template<typename T>
    void set_subtraction_flags(T new_value, T original_value, flags options) {
        T half_max = std::pow(2, sizeof(T) * 4);

        if (options.zero_flag)
            cpu->set_zero_flag(new_value == 0);

        if (options.subtract_flag)
            cpu->set_subtract_flag(true);

        if (options.half_carry_flag) {
            // todo: half-borrow
        }

        if (options.carry_flag)
            cpu->set_carry_flag(new_value > original_value);
    }

public:
    explicit ArithmeticUnit(CPU *cpu);

    void add_registers_8bit(uint8_t register_x, uint8_t register_y);

    void add_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

    void add_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void add_memory_immediate_8bit(uint16_t address, uint8_t immediate_value);

    void add_carry_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

    void add_carry_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void add_carry_register_8bit(uint8_t register_x, uint8_t register_y);

    void sub_registers_8bit(uint8_t register_x, uint8_t register_y);

    void sub_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

    void sub_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void sub_memory_immediate_8bit(uint16_t address, uint8_t immediate_value);

    void sub_carry_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

    void sub_carry_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void sub_carry_register_8bit(uint8_t register_x, uint8_t register_y);

    void increment_register_8bit(uint8_t register_x);

    void increment_indirect_8bit(uint16_t address);

    void decrement_register_8bit(uint8_t register_x);

    void decrement_indirect_8bit(uint16_t address);

    ~ArithmeticUnit();

};

#endif //EMUBOY_ARITHMETICUNIT_H
