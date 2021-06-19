//
// Created by cedric on 2021-06-19.
//

#include <stdexcept>
#include <algorithm>
#include "opcode_parsing_math.h"

uint8_t swap_nibble(uint8_t value)
{
    return ((value & 0x0F) << 4) + ((value & 0xF0) >> 4);
}

bool byte_in_range(uint8_t value, uint8_t lower, uint8_t upper)
{
    if(lower >= upper)
        throw std::runtime_error("Lower bound greater or equal than upper bound!");

    return value >= lower && value <= upper;
}

bool byte_in_range_vertical(uint8_t value, uint8_t lower, uint8_t upper)
{
    value = swap_nibble(value);
    lower = swap_nibble(lower);
    upper = swap_nibble(upper);

    return byte_in_range(value, lower, upper);
}