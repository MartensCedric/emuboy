//
// Created by cedric on 2021-09-07.
//

#include "memory/memory_management_unit.h"
#include <cstdio>
#include <cstring>

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

MemoryManagementUnit::~MemoryManagementUnit() {
    delete [] memory;
}
