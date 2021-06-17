//
// Created by cedric on 2021-06-16.
//

#ifndef GAMEBOY_CPU_H
#define GAMEBOY_CPU_H
#include <cstdint>
#include <cstddef>

class CPU {
    private:
        const static size_t NUM_REGISTERS = 8;
        const static size_t NUM_MEMORY_BYTES = 0xFFFF;

        uint8_t registers[NUM_REGISTERS];
        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t memory[NUM_MEMORY_BYTES];

    public:
        CPU();
        void fetch_cycle();
        ~CPU();
};


#endif //GAMEBOY_CPU_H
