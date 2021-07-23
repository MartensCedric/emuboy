//
// Created by cedric on 2021-06-16.
//

#ifndef EMUBOY_CPU_H
#define EMUBOY_CPU_H
#include <cstdint>
#include <cstddef>
#include <boost/scoped_array.hpp>

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

class CPU {
    private:
        const static size_t NUM_REGISTERS = 8;
        const static size_t NUM_MEMORY_BYTES = 0xFFFF;

        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t* memory = new uint8_t [NUM_MEMORY_BYTES];
        uint8_t* registers = new uint8_t [NUM_REGISTERS];  // B, C, D, E, H, L, F, A

        void process_opcode();

        bool cpu_active = true;
        bool lcd_display_active = true;

        bool interrupts_enabled = true;
    public:
        CPU();
        uint16_t get_stack_pointer() const;
        uint16_t get_program_counter() const;
        const uint8_t* get_registers() const;
        uint16_t get_16bit_register(uint8_t index) const;
        uint8_t fetch() const;
        uint8_t fetch_next();
        void jump_to_address(uint16_t address);

        void increment_pc();
        void increment_pc(uint16_t bytes_to_increment);
        void fetch_cycle();

        void enable_interrupts();
        void disable_interrupts();

        void setZeroFlag(bool isOn);
        void setSubtractFlag(bool isOn);
        void setHalfCarryFlag(bool isOn);
        void setCarryFlag(bool isOn);

        bool isZeroFlagOn();
        bool isSubtractFlagOn();
        bool isHalfCarryFlagOn();
        bool isCarryFlagOn();

        void load_register_immediate(uint8_t reg_x, uint8_t value);
        void load_16bit_register_immediate(uint8_t reg_x, uint16_t value);
        void load_register_indirect(uint8_t reg_x, uint8_t reg_y);
        void load_memory_indirect(uint8_t reg_x, uint16_t memory_address);

        void store_memory_indirect(uint16_t memory_address, uint8_t reg_x);
        void store_memory_immediate(uint16_t memory_address, uint8_t value);

        void push(uint16_t value);
        uint16_t peek() const;
        uint16_t pop();

        void stop();
        void halt();

        ~CPU();
};


#endif //EMUBOY_CPU_H
