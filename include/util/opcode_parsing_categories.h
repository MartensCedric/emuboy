//
// Created by cedric on 2021-06-19.
//

#ifndef EMUBOY_OPCODE_PARSING_CATEGORIES_H
#define EMUBOY_OPCODE_PARSING_CATEGORIES_H

#include "cpu/CPU.h"
/**
 * Categories taken from this website: https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

bool next_is_misc(uint8_t first_byte);
bool next_is_jump_calls(uint8_t first_byte);
bool next_is_8bit_lsm(uint8_t first_byte);
bool next_is_16bit_lsm(uint8_t first_byte);
bool next_is_8bit_arithmetic(uint8_t first_byte);
bool next_is_16bit_arithmetic(uint8_t first_byte);
bool next_is_8bit_rotation_shifts(uint8_t first_byte);

#endif //EMUBOY_OPCODE_PARSING_CATEGORIES_H
