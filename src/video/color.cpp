//
// Created by cedric on 2021-07-17.
//


#include <video/color.h>


Color::Pixel::Pixel(uint8_t shade_value) {
    set_shade_value(shade_value);
}

void Color::Pixel::set_shade_value(uint8_t shade_value)
{
    if(shade_value > COLOR_LIGHTEST)
        throw std::runtime_error("Invalid color!");
    this->shade_value = shade_value;
}
uint8_t Color::Pixel::get_shade_value() const {
    return this->shade_value;
}
