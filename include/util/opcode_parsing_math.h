//
// Created by cedric on 2021-06-19.
//

#ifndef EMUBOY_OPCODE_PARSING_MATH_H
#define EMUBOY_OPCODE_PARSING_MATH_H

uint8_t swap_nibble(uint8_t value);
bool byte_in_range(uint8_t value, uint8_t lower, uint8_t upper);
bool byte_in_range_vertical(uint8_t value, uint8_t lower, uint8_t upper);

#endif //EMUBOY_OPCODE_PARSING_MATH_H
