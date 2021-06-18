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
        constexpr const static uint8_t RESERVED_BYTES[4] = {0xCE, 0xDD, 0xED ,0xFD};


        uint8_t registers[NUM_REGISTERS];
        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t memory[NUM_MEMORY_BYTES];

        void process_opcode();

    public:
        CPU();
        uint16_t get_stack_pointer();
        uint16_t get_program_counter();
        void fetch_cycle();
        ~CPU();
};


#endif //GAMEBOY_CPU_H
