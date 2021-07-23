//
// Created by cedric on 2021-06-19.
//

#ifndef EMUBOY_OPCODE_PARSING_H
#define EMUBOY_OPCODE_PARSING_H

#include "cpu/CPU.h"
#include "opcode_parsing_categories.h"
void call_8bit_lsm(CPU* cpu);
void call_misc(CPU* cpu);
void call_jump_calls(CPU* cpu);
void call_16bit_lsm(CPU* cpu);
void call_8bit_arithmetic(CPU* cpu);
void call_16bit_arithmetic(CPU* cpu);
void call_8bit_rotation_shifts(CPU* cpu);
#endif //EMUBOY_OPCODE_PARSING_H
