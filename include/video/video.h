//
// Created by cedric on 2021-07-17.
//

#ifndef EMUBOY_VIDEO_H
#define EMUBOY_VIDEO_H

#include <cstdint>
#include <cstddef>
#include "video/frame_buffer.h"
#include "memory/memory_management_unit.h"

class Video {
private:
    uint8_t clock;
    uint8_t mode;
    uint8_t line;

    FrameBuffer* frame;
    MemoryManagementUnit mmu;

    uint8_t get_scroll_x() const;
    uint8_t get_scroll_y() const;

public:
    Video(MemoryManagementUnit& mmu);
    ~Video();
};

#endif //EMUBOY_VIDEO_H
