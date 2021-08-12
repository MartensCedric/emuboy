//
// Created by cedric on 2021-08-11.
//

#ifndef EMUBOY_SHIFTING_UNIT_H
#define EMUBOY_SHIFTING_UNIT_H
#include <cmath>
#include "cpu/CPU.h"
#include "cpu/flags.h"
#include "memory/memory_management_unit.h"

class ShiftingUnit
{
    private:
        CPU* cpu;
    public:
        explicit ShiftingUnit(CPU* cpu);
        void set_bit(uint8_t bit, uint8_t register_x);
        void reset_bit(uint8_t bit, uint8_t register_x);
        ~ShiftingUnit();
};

#endif //EMUBOY_SHIFTING_UNIT_H
