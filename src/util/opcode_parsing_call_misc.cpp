//
// Created by cedric on 2021-08-17.
//

/**
 * To understand what is going in this file, it is critical that
 * the reader follows with this table:
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

#include <cpu/CPU.h>
#include <util/opcode_parsing_8bit_rotation_shifts.h>
#include <stdexcept>

void call_misc(CPU *cpu) {
    uint8_t first_byte = cpu->fetch_byte();

    switch (first_byte) {
        case 0x00:
            // nop
            break;
        case 0x10:
            cpu->stop();
            break;
        case 0x76:
            cpu->halt();
            break;
        case 0xCB:
            cpu->fetch_next_byte();
            call_8bit_rotation_shifts(cpu);
            break;
        case 0xF3:
            cpu->disable_interrupts();
            break;
        case 0xFB:
            cpu->enable_interrupts();
            break;
        default:
            throw std::runtime_error("Cannot find misc instruction!");
    }
}


