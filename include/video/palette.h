//
// Created by cedric on 2021-09-09.
//

#ifndef EMUBOY_PALETTE_H
#define EMUBOY_PALETTE_H

#include <stdint.h>
#include <cstddef>
#include "color.h"

namespace Gameboy_Color
{
    class Palette
    {
    private:
        uint8_t red_value[4];
        uint8_t green_value[4];
        uint8_t blue_value[4];

        void initialize_palette(Color& color, uint8_t palette_level);

    public:
        Palette(Color lightest, Color light, Color dark, Color darkest);
        Color operator[](std::size_t index);
        ~Palette();
    };
}
#endif //EMUBOY_PALETTE_H
