//
// Created by cedric on 2021-07-17.
//

#include "video/frame_buffer.h"

FrameBuffer::FrameBuffer(std::size_t width, std::size_t  height) : width(width), height(height) {
    size_t size = width * height;
    this->buffer = (Gameboy_Color::Pixel *) malloc(size * sizeof(Gameboy_Color::Pixel));
}

void FrameBuffer::set_pixel(uint8_t x, uint8_t y, Gameboy_Color::Pixel pixel) {
    this->buffer[get_index(x, y)] = pixel;
}

Gameboy_Color::Pixel FrameBuffer::get_pixel(uint8_t x, uint8_t y) {
    return this->buffer[get_index(x, y)];
}

FrameBuffer::~FrameBuffer() {
    free(this->buffer);
}
