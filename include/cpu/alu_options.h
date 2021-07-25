//
// Created by cedric on 2021-07-24.
//

#ifndef EMUBOY_FLAG_REGISTER_H
#define EMUBOY_FLAG_REGISTER_H

typedef struct alu_options {
    bool allow_zero_flag = false;
    bool allow_subtract_flag = false;
    bool allow_half_carry_flag = false;
    bool allow_carry_flag = false;
} alu_options;

#define ALU_ALL_FLAGS { true, true, true, true }
#define ALU_NO_FLAGS { false, false, false, false }

#endif //EMUBOY_FLAG_REGISTER_H
