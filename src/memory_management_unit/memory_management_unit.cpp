//
// Created by cedric on 2021-09-07.
//

#include "memory/memory_management_unit.h"
#include <cstdio>
#include <cstring>

#define REG_SCROLL_X 0xFF43
#define REG_SCROLL_Y 0xFF42

MemoryManagementUnit::MemoryManagementUnit() {
    this->memory = new uint8_t [NUM_MEMORY_BYTES];
    memset(this->memory, 0, NUM_MEMORY_BYTES);
}

uint8_t& MemoryManagementUnit::operator[](std::size_t index) {
    return this->memory[index];
};

uint8_t &MemoryManagementUnit::operator[](std::size_t index) const {
    return this->memory[index];
}

uint8_t MemoryManagementUnit::get_scroll_x() const {
    return this->memory[REG_SCROLL_X];
}

void MemoryManagementUnit::set_scroll_x(uint8_t value) {
    this->memory[REG_SCROLL_X] = value;
}

uint8_t MemoryManagementUnit::get_scroll_y() const {
    return this->memory[REG_SCROLL_Y];
}

void MemoryManagementUnit::set_scroll_y(uint8_t value) {
    this->memory[REG_SCROLL_Y] = value;
}

MemoryManagementUnit::~MemoryManagementUnit() {
    delete [] memory;
}
