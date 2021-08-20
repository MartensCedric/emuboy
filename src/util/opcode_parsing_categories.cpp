//
// Created by cedric on 2021-06-19.
//
#include <initializer_list>
#include "opcode_parsing_categories.h"
#include "opcode_parsing_math.h"

/**
 * This grid is critical for the understanding of this section.
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

bool next_is_misc(const uint8_t first_byte) {
    return is_in<uint8_t>(first_byte, {0x00, 0x10, 0x76, 0xF3, 0xFB});
}

bool next_is_jump_calls(const uint8_t first_byte) {
    if (is_in<uint8_t>(first_byte, {0x20, 0x30, 0xC0, 0xD0}))
        return true;

    if (byte_in_range_vertical(first_byte, 0x18, 0x38))
        return true;

    if (byte_in_range(first_byte, 0xC2, 0xC4))
        return true;

    if (byte_in_range(first_byte, 0xC7, 0xCA))
        return true;

    if (is_in<uint8_t>(first_byte, {0xD2, 0xD4}))
        return true;

    if (byte_in_range(first_byte, 0xD7, 0xDA))
        return true;

    if (byte_in_range_vertical(first_byte, 0xCF, 0xFF))
        return true;

    if (is_in<uint8_t>(first_byte, {0xCC, 0xCD, 0xDC, 0xE7, 0xE9, 0xF7}))
        return true;

    return false;
}

bool next_is_8bit_lsm(const uint8_t first_byte) {
    if (byte_in_range(first_byte, 0x40, 0x4F))
        return true;

    if (byte_in_range(first_byte, 0x50, 0x5F))
        return true;

    if (byte_in_range(first_byte, 0x60, 0x6F))
        return true;

    if (byte_in_range(first_byte, 0x70, 0x75))
        return true;

    if (byte_in_range(first_byte, 0x77, 0x7F))
        return true;

    if (byte_in_range_vertical(first_byte, 0x02, 0x32))
        return true;

    if (byte_in_range_vertical(first_byte, 0x06, 0x36))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0A, 0x3A))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0E, 0x3E))
        return true;

    if (is_in<uint8_t>(first_byte, {0xE0, 0xF0, 0xE2, 0xF2, 0xEA, 0xFA}))
        return true;

    return false;
}

bool next_is_16bit_lsm(const uint8_t first_byte) {
    if (byte_in_range_vertical(first_byte, 0x01, 0x31))
        return true;

    if (byte_in_range_vertical(first_byte, 0xC1, 0xF1))
        return true;

    if (byte_in_range_vertical(first_byte, 0xC5, 0xF5))
        return true;

    if (is_in<uint8_t>(first_byte, {0x08, 0xF8, 0xF9}))
        return true;
    return false;
}

bool next_is_8bit_arithmetic(const uint8_t first_byte) {
    if (byte_in_range(first_byte, 0x80, 0x8F))
        return true;

    if (byte_in_range(first_byte, 0x90, 0x9F))
        return true;

    if (byte_in_range(first_byte, 0xA0, 0xAF))
        return true;

    if (byte_in_range(first_byte, 0xB0, 0xBF))
        return true;

    if (byte_in_range_vertical(first_byte, 0x27, 0x37))
        return true;

    if (byte_in_range_vertical(first_byte, 0x04, 0x34))
        return true;

    if (byte_in_range_vertical(first_byte, 0x05, 0x35))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0C, 0x3C))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0D, 0x3D))
        return true;

    if (byte_in_range_vertical(first_byte, 0x2F, 0x3F))
        return true;

    if (byte_in_range_vertical(first_byte, 0xC6, 0xF6))
        return true;

    if (byte_in_range_vertical(first_byte, 0xCE, 0xFE))
        return true;

    if (is_in<uint8_t>(first_byte, {0xE0, 0xF0, 0xE2, 0xF2, 0xEA, 0xFA}))
        return true;

    return false;
}

bool next_is_16bit_arithmetic(const uint8_t first_byte) {
    if (byte_in_range_vertical(first_byte, 0x03, 0x33))
        return true;

    if (byte_in_range_vertical(first_byte, 0x09, 0x39))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0B, 0x3B))
        return true;

    return first_byte == 0xE8;
}

bool next_is_8bit_rotation_shifts(const uint8_t first_byte) {
    if (byte_in_range_vertical(first_byte, 0x07, 0x17))
        return true;

    if (byte_in_range_vertical(first_byte, 0x0F, 0x1F))
        return true;

    return first_byte == 0xCB;
}