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

        uint8_t registers[NUM_REGISTERS]; // B, C, D, E, H, L, A, F
        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t memory[NUM_MEMORY_BYTES];

        void process_opcode();

    public:
        CPU();
        uint16_t get_stack_pointer() const;
        uint16_t get_program_counter() const;
        uint8_t fetch() const;
        void jump_to_address(uint16_t address);

        void increment_pc();
        void increment_pc(uint16_t bytes_to_increment);
        void fetch_cycle();

        void load_immediate(uint8_t reg_x, uint8_t immediate_value);
        void load_register_indirect(uint8_t reg_x, uint8_t reg_y);
        void load_memory_indirect(uint8_t reg_x, uint16_t memory_address);

        void store_memory_indirect(uint16_t memory_address, uint8_t reg_x);

        ~CPU();
};


#endif //EMUBOY_CPU_H
