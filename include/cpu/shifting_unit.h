//
// Created by cedric on 2021-08-11.
//

#ifndef EMUBOY_SHIFTING_UNIT_H
#define EMUBOY_SHIFTING_UNIT_H

#include <cmath>
#include "cpu/CPU.h"
#include "cpu/flags.h"
#include "memory/memory_management_unit.h"

class ShiftingUnit {
private:
    CPU *cpu;
public:
    explicit ShiftingUnit(CPU *cpu);

    void set_bit_register(uint8_t bit, uint8_t register_x);

    void set_bit_memory_indirect(uint8_t bit, uint16_t address);

    void reset_bit_register(uint8_t bit, uint8_t register_x);

    void reset_bit_memory_indirect(uint8_t bit, uint16_t address);

    void test_bit_register(uint8_t bit, uint8_t register_x);

    void test_bit_memory_indirect(uint8_t bit, uint16_t address);

    ~ShiftingUnit();
};

#endif //EMUBOY_SHIFTING_UNIT_H
