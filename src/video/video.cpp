//
// Created by cedric on 2021-09-07.
//

#include "video/video.h"

Video::Video(MemoryManagementUnit* mmu) {
    this->mode = 0;
    this->clock = 0;
    this->mmu = mmu;
    this->frame = new FrameBuffer(256, 256);
}

uint8_t Video::get_scroll_x() const {
    return this->mmu->memory[0xFF43];
}

uint8_t Video::get_scroll_y() const {
    return this->mmu->memory[0xFF42];
}


Video::~Video()
{
    delete frame;
}