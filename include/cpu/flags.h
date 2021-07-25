//
// Created by cedric on 2021-07-24.
//

#ifndef EMUBOY_FLAG_REGISTER_H
#define EMUBOY_FLAG_REGISTER_H

typedef struct flags {
    bool zero_flag = false;
    bool subtract_flag = false;
    bool half_carry_flag = false;
    bool carry_flag = false;
} flags;

typedef flags flag_options;

#define FLAGS_ALL { true, true, true, true }
#define FLAGS_ZERO_ONLY { true, false, false, false }
#define FLAGS_SUBTRACT_ONLY { false, true, false, false }
#define FLAGS_HALF_CARRY_ONLY { false, false, true, false }
#define FLAGS_CARRY_ONLY { false, false, false, true }
#define FLAGS_NONE { false, false, false, false }

#endif //EMUBOY_FLAG_REGISTER_H
