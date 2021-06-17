//
// Created by cedric on 2021-06-16.
//

#include "../include/CPU.h"
#include <stdio.h>
#include <cstring>
#include <malloc.h>
#include <cstdlib>

CPU::CPU() {
    memset(this->memory, 0, NUM_MEMORY_BYTES);
    memset(this->registers, 0, NUM_REGISTERS);
    this->stack_pointer = NUM_MEMORY_BYTES - 1;
    this->program_counter = 0x100;
}

CPU::~CPU() {
    free(this->memory);
    free(this->registers);
}

void CPU::fetch_cycle() {

}
