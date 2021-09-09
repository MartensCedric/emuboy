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


bool Video::is_background_on() const {
    return static_cast<bool>(mmu.get_lcd_control() & 1);
}

bool Video::is_sprites_on() const {
    return static_cast<bool>((mmu.get_lcd_control() >> 1) & 1);
}

uint8_t Video::sprite_width() const {
    bool width_8 = !static_cast<bool>((mmu.get_lcd_control() >> 2) & 1);

    return width_8 ? 8 : 16;
}

bool Video::use_tile_map_0() const {
    return !static_cast<bool>((mmu.get_lcd_control() >> 3) & 1);
}

bool Video::use_tile_set_0() const {
    return !static_cast<bool>((mmu.get_lcd_control() >> 4) & 1);
}

bool Video::is_window_on() const {
    return static_cast<bool>((mmu.get_lcd_control() >> 5) & 1);
}

bool Video::use_window_tile_map_0() const {
    return !static_cast<bool>((mmu.get_lcd_control() >> 6) & 1);
}

bool Video::is_display_on() const {
    return static_cast<bool>((mmu.get_lcd_control() >> 7) & 1);
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
