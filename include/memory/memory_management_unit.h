//
// Created by cedric on 2021-07-22.
//

#ifndef EMUBOY_MEMORY_MANAGEMENT_UNIT_H
#define EMUBOY_MEMORY_MANAGEMENT_UNIT_H

#include <stdint.h>
#include <stdlib.h>
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
    uint8_t* memory;

public:
    uint8_t& operator[](std::size_t index);
    uint8_t& operator[](std::size_t index) const;

    explicit MemoryManagementUnit();

    uint8_t get_scroll_x() const;
    void set_scroll_x(uint8_t value);

    uint8_t get_scroll_y() const;
    void set_scroll_y(uint8_t value);

    uint8_t* get_tile_data_table() const;

    uint8_t get_lcd_control() const;
    ~MemoryManagementUnit();
};

#endif //EMUBOY_MEMORY_MANAGEMENT_UNIT_H
