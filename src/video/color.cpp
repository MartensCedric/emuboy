//
// Created by cedric on 2021-07-17.
//


#include <video/color.h>


Color::Pixel::Pixel(uint8_t value) {
    set_pixel_value(value);
}

void Color::Pixel::set_pixel_value(uint8_t value)
{
    if(value > COLOR_LIGHTEST)
        throw std::runtime_error("Invalid color!");
    this->pixel_value = value;
}
uint8_t Color::Pixel::get_pixel_value() const {
    return pixel_value;
}
