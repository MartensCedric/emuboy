//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_ARITHMETICUNIT_H
#define EMUBOY_ARITHMETICUNIT_H

#include "cpu/CPU.h"
#include "cpu/alu_options.h"

class ArithmeticUnit
{
    void add_registers_8bit(uint8_t register_x, uint8_t register_y);
    void add_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);
    void add_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void sub_registers_8bit(uint8_t register_x, uint8_t register_y);
    void sub_register_immediate_8bit(uint8_t register_x, uint8_t immediate_value);
    void sub_register_indirect_8bit(uint8_t register_x, uint16_t address);

    void increment_register(uint8_t register_x);
    void increment_indirect(uint16_t address);

    void decrement_register(uint8_t register_x);
    void decrement_indirect(uint16_t address);
};
#endif //EMUBOY_ARITHMETICUNIT_H
