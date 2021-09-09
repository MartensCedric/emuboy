//
// Created by cedric on 2021-09-09.
//

#include "video/color.h"

Gameboy_Color::Color::Color(uint8_t red_value, uint8_t green_value, uint8_t blue_value) :
        red_value(red_value),
        green_value(green_value),
        blue_value(blue_value) {
}


uint8_t Gameboy_Color::Color::get_red_value() const {
    return red_value;
}

uint8_t Gameboy_Color::Color::get_green_value() const {
    return green_value;
}

uint8_t Gameboy_Color::Color::get_blue_value() const {
    return blue_value;
}

Gameboy_Color::Color::~Color() {

}

