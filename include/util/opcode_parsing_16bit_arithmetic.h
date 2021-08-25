//
// Created by cedric on 2021-08-17.
//

#ifndef EMUBOY_OPCODE_PARSING_16BIT_ARITHMETIC_H
#define EMUBOY_OPCODE_PARSING_16BIT_ARITHMETIC_H
#include "cpu/CPU.h"
#include "opcode_parsing_categories.h"
void register_16bit_arithmetic_opcodes(CPU* cpu);
void call_16bit_arithmetic(CPU* cpu);
#endif //EMUBOY_OPCODE_PARSING_16BIT_ARITHMETIC_H
