//
// Created by cedric on 2021-09-07.
//

#include "memory/memory_management_unit.h"
#include <cstdio>
#include <cstring>

MemoryManagementUnit::MemoryManagementUnit() {
    memset(this->memory, 0, NUM_MEMORY_BYTES);
}

MemoryManagementUnit::~MemoryManagementUnit() {
    delete [] memory;
};