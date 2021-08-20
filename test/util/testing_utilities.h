//
// Created by cedric on 2021-06-20.
//

#ifndef EMUBOY_TESTING_UTILITIES_H
#define EMUBOY_TESTING_UTILITIES_H

#include "cpu/CPU.h"
#include <initializer_list>
#include <algorithm>

void set_next_opcode(CPU *cpu, std::initializer_list<uint8_t> opcode);

void run_next_opcode(CPU *cpu, std::initializer_list<uint8_t> opcode);

void set_flags(CPU *cpu, flags flags);

#endif //EMUBOY_TESTING_UTILITIES_H
