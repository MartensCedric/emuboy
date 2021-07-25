//
// Created by cedric on 2021-06-16.
//

#ifndef EMUBOY_CPU_H
#define EMUBOY_CPU_H
#include <cstdint>
#include <cstddef>
#include <boost/scoped_array.hpp>

class ArithmeticUnit;
class LogicUnit;

class CPU {
    private:
        const static size_t NUM_REGISTERS = 8;
        const static size_t NUM_MEMORY_BYTES = 0xFFFF;

        uint16_t stack_pointer;
        uint16_t program_counter;
        uint8_t* memory = new uint8_t [NUM_MEMORY_BYTES];
        uint8_t* registers = new uint8_t [NUM_REGISTERS];  // B, C, D, E, H, L, F, A

        ArithmeticUnit* arithmetic_unit;
        LogicUnit* logic_unit;

        void set_zero_flag(bool is_on);
        void set_subtract_flag(bool is_on);
        void set_half_carry_flag(bool is_on);
        void set_carry_flag(bool is_on);

        void process_opcode();

        bool cpu_active = true;
        bool lcd_display_active = true;

        bool should_increment_pc = true;

        bool interrupts_enabled = true;
        friend class ArithmeticUnit;
        friend class LogicUnit;

    public:
        CPU();
        uint16_t get_stack_pointer() const;
        uint16_t get_program_counter() const;
        const uint8_t* get_registers() const;
        uint16_t get_16bit_register(uint8_t index) const;

        ArithmeticUnit* get_arithmetic_unit() const;
        LogicUnit* get_logic_unit() const;

        uint8_t fetch_byte() const;
        uint8_t fetch_next_byte();
        uint16_t fetch_next_word();
        void jump_to_address(uint16_t address);

        void increment_pc();
        void increment_pc(uint16_t bytes_to_increment);
        void fetch_cycle();

        void enable_interrupts();
        void disable_interrupts();

        void load_register_immediate(uint8_t reg_x, uint8_t value);
        void load_16bit_register_immediate(uint8_t reg_x, uint16_t value);
        void load_register_indirect(uint8_t reg_x, uint8_t reg_y);
        void load_memory_indirect(uint8_t reg_x, uint16_t memory_address);

        uint8_t get_byte_memory_indirect(uint8_t reg_x);
        uint16_t get_word_memory_indirect(uint8_t reg_x);

        void store_memory_indirect(uint16_t memory_address, uint8_t reg_x);
        void store_memory_immediate(uint16_t memory_address, uint8_t value);

        void push(uint16_t value);
        uint16_t peek() const;
        uint16_t pop();

        void stop();
        void halt();

        bool is_cpu_active() const;
        bool is_lcd_display_active() const;

        bool is_zero_flag_on();
        bool is_subtract_flag_on();
        bool is_half_carry_flag_on();
        bool is_carry_flag_on();


     ~CPU();

};

#include "cpu/arithmetic_unit.h"
#include "cpu/logic_unit.h"

#endif //EMUBOY_CPU_H
