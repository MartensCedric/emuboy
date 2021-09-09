//
// Created by cedric on 2021-09-09.
//

#ifndef EMUBOY_COLOR_H
#define EMUBOY_COLOR_H

#include <stdint.h>

namespace Gameboy_Color{
    class Color
    {
    private:
        const uint8_t red_value;
        const uint8_t green_value;
        const uint8_t blue_value;

    public:
        Color(uint8_t red_value, uint8_t green_value, uint8_t blue_value);
        uint8_t get_red_value() const;
        uint8_t get_green_value() const;
        uint8_t get_blue_value() const;
        ~Color();
    };
}

#endif //EMUBOY_COLOR_H
