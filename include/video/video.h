//
// Created by cedric on 2021-07-17.
//

#ifndef EMUBOY_VIDEO_H
#define EMUBOY_VIDEO_H

#include <cstdint>
#include <cstddef>
#include <video/palette.h>
#include "video/frame_buffer.h"
#include "memory/memory_management_unit.h"

const Gameboy_Color::Palette EQUIDISTANT = Gameboy_Color::Palette(
        Gameboy_Color::Color(255, 255, 255),
        Gameboy_Color::Color(192, 192, 192),
        Gameboy_Color::Color(96, 96, 96),
        Gameboy_Color::Color(0,0,0));

enum VideoMode {HORIZONTAL_BLANK, VERTICAL_BLANK, SCANLINE_SPRITE, SCANLINE_VIDEO_RAM};

class Video {
private:
    uint32_t clock;
    VideoMode mode;
    uint8_t line;
    Gameboy_Color::Palette palette = EQUIDISTANT;

    FrameBuffer* frame;
    MemoryManagementUnit mmu;

public:
    Video(MemoryManagementUnit& mmu);

    void step();

    void scan_line(uint8_t line_number);
    void horizontal_blank();


    uint8_t get_scroll_x() const;
    uint8_t get_scroll_y() const;

    ~Video();
};

#endif //EMUBOY_VIDEO_H
