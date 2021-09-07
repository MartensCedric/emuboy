//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_MEMORY_MANAGEMENT_UNIT_H
#define EMUBOY_MEMORY_MANAGEMENT_UNIT_H

#include <stdint.h>
#define NUM_MEMORY_BYTES 0xFFFF

#define REGISTER_A_INDEX 7
#define REGISTER_B_INDEX 0
#define REGISTER_C_INDEX 1
#define REGISTER_D_INDEX 2
#define REGISTER_E_INDEX 3
#define REGISTER_F_INDEX 6
#define REGISTER_H_INDEX 4
#define REGISTER_L_INDEX 5

#define REGISTER_AF_INDEX 0
#define REGISTER_BC_INDEX 1
#define REGISTER_DE_INDEX 2
#define REGISTER_HL_INDEX 3
#define REGISTER_SP_INDEX 4

class MemoryManagementUnit {
private:


    MemoryManagementUnit();
    ~MemoryManagementUnit();

public:
    uint8_t* memory; //todo: find a clean way to do this, perhaps have getters for some registers and a raw pointer one
};

#endif //EMUBOY_MEMORY_MANAGEMENT_UNIT_H
