//
// Created by cedric on 2021-08-17.
//

/**
 * To understand what is going in this file, it is critical that
 * the reader follows with this table:
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

#include <cpu/CPU.h>
#include <stdexcept>

void register_misc_opcodes(CPU *cpu) {
    cpu->register_opcode("NOP",
                         [](uint16_t opcode) { return opcode == 0x00; },
                         [](CPU *cpu) {});

    cpu->register_opcode("STOP",
                         [](uint16_t opcode) { return opcode == 0x10; },
                         [](CPU *cpu) {
                             cpu->stop();
                         });

    cpu->register_opcode("HALT",
                         [](uint16_t opcode) { return opcode == 0x76; },
                         [](CPU *cpu) {
                             cpu->halt();
                         });

    cpu->register_opcode("Disable Interrupts",
                         [](uint16_t opcode) { return opcode == 0xF3; },
                         [](CPU *cpu) {
                             cpu->halt();
                         });

    cpu->register_opcode("Enable Interrupts",
                         [](uint16_t opcode) { return opcode == 0xFB; },
                         [](CPU *cpu) {
                             cpu->halt();
                         });
}