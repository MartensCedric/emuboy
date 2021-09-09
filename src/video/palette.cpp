//
// Created by cedric on 2021-09-09.
//

#include <video/palette.h>
#include <video/color.h>
#include "assert.h"


Gameboy_Color::Palette::Palette(Color lightest, Color light, Color dark, Color darkest) {

    initialize_palette(lightest, 0);
    initialize_palette(light, 1);
    initialize_palette(dark, 2);
    initialize_palette(darkest, 3);
}


void Gameboy_Color::Palette::initialize_palette(Color &color, uint8_t palette_level) {
    red_value[palette_level] = color.get_red_value();
    green_value[palette_level] = color.get_green_value();
    blue_value[palette_level] = color.get_blue_value();
}

Gameboy_Color::Color Gameboy_Color::Palette::operator[](std::size_t index) {
    return Color(red_value[index], green_value[index], blue_value[index]);
}


Gameboy_Color::Palette::~Palette() {}


