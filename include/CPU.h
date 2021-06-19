//
// Created by cedric on 2021-06-16.
//

#ifndef EMUBOY_CPU_H
#define EMUBOY_CPU_H
#include <cstdint>
#include <cstddef>

class CPU {
    private:
        const static size_t NUM_REGISTERS = 8;
        const static size_t NUM_MEMORY_BYTES = 0xFFFF;

        uint8_t registers[NUM_REGISTERS]; // B, C, D, E, H, L
        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t memory[NUM_MEMORY_BYTES];

        void process_opcode();

    public:
        CPU();
        uint16_t get_stack_pointer() const;
        uint16_t get_program_counter() const;
        uint8_t get_first_opcode_byte() const;
        void fetch_cycle();
        ~CPU();
};


#endif //EMUBOY_CPU_H
