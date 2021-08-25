//
// Created by cedric on 2021-08-17.
//

#ifndef EMUBOY_OPCODE_PARSING_MISC_H
#define EMUBOY_OPCODE_PARSING_MISC_H
#include "cpu/CPU.h"
#include "opcode_parsing_categories.h"
void register_misc_opcodes(CPU* cpu);
void call_misc(CPU* cpu);
#endif //EMUBOY_OPCODE_PARSING_MISC_H
