//
// Created by cedric on 2021-08-17.
//

#ifndef EMUBOY_OPCODE_PARSING_JUMP_CALLS_H
#define EMUBOY_OPCODE_PARSING_JUMP_CALLS_H
#include "cpu/CPU.h"
#include "opcode_parsing_categories.h"
void register_jump_calls_opcodes(CPU* cpu);
void call_jump_calls(CPU* cpu);
#endif //EMUBOY_OPCODE_PARSING_JUMP_CALLS_H
