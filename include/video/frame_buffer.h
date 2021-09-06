//
// Created by cedric on 2021-07-17.
//

#ifndef EMUBOY_FRAME_BUFFER_H
#define EMUBOY_FRAME_BUFFER_H

#include <cstdint>
#include "color.h"

class FrameBuffer {
private:
    Color::Pixel *buffer;
    const uint8_t width;
    const uint8_t height;

    inline size_t get_index(uint8_t x, uint8_t y) { return height * y + x; };
public:
    FrameBuffer(uint8_t width, uint8_t height);

    void set_pixel(uint8_t x, uint8_t y, Color::Pixel pixel);

    Color::Pixel get_pixel(uint8_t x, uint8_t y);

    ~FrameBuffer();
};

#endif //EMUBOY_FRAME_BUFFER_H
