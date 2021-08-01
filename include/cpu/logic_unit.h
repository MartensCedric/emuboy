//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_LOGICUNIT_H
#define EMUBOY_LOGICUNIT_H

#include <cmath>
#include "cpu/CPU.h"
#include "cpu/flags.h"
#include "memory/memory_management_unit.h"


class LogicUnit
{
    private:
        CPU* cpu;

        template<typename T>
        void set_or_flags(T new_value, T original_value)
        {
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(false);
            cpu->set_half_carry_flag(false);
            cpu->set_carry_flag(false);
        }

        template<typename T>
        void set_and_flags(T new_value, T original_value)
        {
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(false);
            cpu->set_half_carry_flag(true);
            cpu->set_carry_flag(false);
        }

        template<typename T>
        void set_xor_flags(T new_value, T original_value)
        {
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(false);
            cpu->set_half_carry_flag(false);
            cpu->set_carry_flag(false);
        }

        template<typename T>
        void set_compare_flags(T new_value, T original_value)
        {
            T half_max= std::pow(2, sizeof(T) * 4);
            cpu->set_zero_flag(new_value == 0);
            cpu->set_subtract_flag(true);
            cpu->set_half_carry_flag(new_value < half_max && original_value >= half_max);
            cpu->set_carry_flag(new_value > original_value);
        }

    public:
        explicit LogicUnit(CPU* cpu);

        void compare_registers_8bit(uint8_t register_x, uint8_t register_y);
        void compare_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

        void logic_or_registers_8bit(uint8_t register_x, uint8_t register_y);
        void logic_or_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

        void logic_and_registers_8bit(uint8_t register_x, uint8_t register_y);
        void logic_and_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

        void logic_xor_registers_8bit(uint8_t register_x, uint8_t register_y);
        void logic_xor_immediate_8bit(uint8_t register_x, uint8_t immediate_value);

        void set_carry_flag();
        void complement_carry_flag();
        void complement_register(uint8_t register_x);

        ~LogicUnit();
};

#endif //EMUBOY_LOGICUNIT_H
