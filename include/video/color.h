//
// Created by cedric on 2021-07-17.
//

#ifndef EMUBOY_COLOR_H
#define EMUBOY_COLOR_H
#include <stdexcept>

namespace Color {
    const uint8_t COLOR_DARKEST = 0;
    const uint8_t COLOR_DARK = 1;
    const uint8_t COLOR_LIGHT = 2;
    const uint8_t COLOR_LIGHTEST = 3;

    class Pixel
    {
        private:
            uint8_t pixel_value;
        public:
            Pixel(uint8_t value);
            void set_pixel_value(uint8_t value);
            uint8_t get_pixel_value() const;
    };
}

#endif //EMUBOY_COLOR_H
