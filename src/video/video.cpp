//
// Created by cedric on 2021-09-07.
//

#include "video/video.h"

Video::Video(MemoryManagementUnit& mmu) {
    this->mode = HORIZONTAL_BLANK;
    this->clock = 0;
    this->mmu = mmu;
    this->frame = new FrameBuffer(256, 256);
}

uint8_t Video::get_scroll_x() const {
    return this->mmu[0xFF43];
}

uint8_t Video::get_scroll_y() const {
    return this->mmu[0xFF42];
}

void Video::step() {
//    clock++;
//
//    switch (mode) {
//        case HORIZONTAL_BLANK:
//            break;
//        case VERTICAL_BLANK:
//            break;
//        case SCANLINE_SPRITE:
//            break;
//        case SCANLINE_VIDEO_RAM:
//            break;
//        default:
//            break;
//    }
}

Video::~Video()
{
    delete frame;
}