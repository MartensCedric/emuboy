//
// Created by cedric on 2021-07-17.
//

#ifndef EMUBOY_FRAME_BUFFER_H
#define EMUBOY_FRAME_BUFFER_H

#include <cstdint>
#include "pixel.h"

class FrameBuffer {
private:
    uint8_t* memory_map = nullptr;
    Gameboy_Color::Pixel *buffer;
    const uint8_t width;
    const uint8_t height;

    inline size_t get_index(uint8_t x, uint8_t y) { return height * y + x; };
public:
    FrameBuffer(std::size_t width, std::size_t height);

    void set_pixel(uint8_t x, uint8_t y, Gameboy_Color::Pixel pixel);

    Gameboy_Color::Pixel get_pixel(uint8_t x, uint8_t y);

    ~FrameBuffer();
};

#endif //EMUBOY_FRAME_BUFFER_H
