//
// Created by cedric on 2021-06-19.
//

#ifndef EMUBOY_OPCODE_PARSING_H
#define EMUBOY_OPCODE_PARSING_H

#include "CPU.h"
/**
 * Categories taken from this website: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

bool next_is_misc(const CPU* cpu);
bool next_is_jump_calls(const CPU* cpu);
bool next_is_8bit_lsm(const CPU* cpu);
bool next_is_16bit_lsm(const CPU* cpu);
bool next_is_8bit_arithmetic(const CPU* cpu);
bool next_is_16bit_arithmetic(const CPU* cpu);
bool next_is_8bit_rotation_shifts(const CPU* cpu);

#endif //EMUBOY_OPCODE_PARSING_H
