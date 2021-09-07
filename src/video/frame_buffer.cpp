//
// Created by cedric on 2021-07-17.
//

#include "video/frame_buffer.h"

FrameBuffer::FrameBuffer(uint8_t width, uint8_t height) : width(width), height(height) {
    size_t size = width * height;
    this->buffer = (Color::Pixel *) malloc(size * sizeof(Color::Pixel));
}



void FrameBuffer::set_pixel(uint8_t x, uint8_t y, Color::Pixel pixel) {
    this->buffer[get_index(x, y)] = pixel;
}

Color::Pixel FrameBuffer::get_pixel(uint8_t x, uint8_t y) {
    return this->buffer[get_index(x, y)];
}

FrameBuffer::~FrameBuffer() {
    free(this->buffer);
}
