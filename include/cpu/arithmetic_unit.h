//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_ARITHMETICUNIT_H
#define EMUBOY_ARITHMETICUNIT_H

#include <cmath>
#include "cpu/CPU.h"
#include "cpu/flags.h"
#include "memory/memory_management_unit.h"


class ArithmeticUnit
{
    private:
        CPU* cpu;

        template<typename T>
        void set_addition_flags(T new_value, T original_value)
        {
            T half_max= std::pow(2, sizeof(T) * 4);
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(false);
            cpu->set_half_carry_flag(new_value >= half_max && original_value < half_max);
            cpu->set_carry_flag(new_value < original_value);
        }

        template<typename T>
        void set_subtraction_flags(T new_value, T original_value)
        {
            T half_max= std::pow(2, sizeof(T) * 4);
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(true);
            cpu->set_half_carry_flag(new_value < half_max && original_value >= half_max);
            cpu->set_carry_flag(new_value > original_value);
        }

    public:
        explicit ArithmeticUnit(CPU* cpu);

        void add_registers_8bit(uint8_t register_x, uint8_t register_y);
        void add_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);
        void add_register_indirect_8bit(uint8_t register_x, uint16_t address);
        void add_memory_immediate_8bit(uint16_t address, uint8_t immediate_value);
        void add_carry_registers_8bit(uint8_t register_x, uint8_t immediate_value);

        void sub_registers_8bit(uint8_t register_x, uint8_t register_y);
        void sub_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);
        void sub_register_indirect_8bit(uint8_t register_x, uint16_t address);
        void sub_memory_immediate_8bit(uint16_t address, uint8_t immediate_value);
        void sub_carry_registers_8bit(uint8_t register_x, uint8_t immediate_value);

        void increment_register_8bit(uint8_t register_x);
        void increment_indirect_8bit(uint16_t address);

        void decrement_register_8bit(uint8_t register_x);
        void decrement_indirect_8bit(uint16_t address);

        ~ArithmeticUnit();

};
#endif //EMUBOY_ARITHMETICUNIT_H
