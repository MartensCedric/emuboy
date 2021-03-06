//
// Created by cedric on 2021-06-16.
//

#include "cpu/CPU.h"
#include <cstring>
#include <stdexcept>
#include <util/opcode_parsing_8bit_lsm.h>
#include <util/opcode_parsing_8bit_arithmetic.h>
#include <util/opcode_parsing_16bit_lsm.h>
#include <util/opcode_parsing_16bit_arithmetic.h>
#include <util/opcode_parsing_8bit_rotation_shifts.h>
#include <util/opcode_parsing_jump_calls.h>
#include <util/opcode_parsing_misc.h>
#include "safety.h"
#include "memory/memory_management_unit.h"

CPU::CPU() {
    memset(this->registers, 0, NUM_REGISTERS);
    this->stack_pointer = NUM_MEMORY_BYTES;
    this->program_counter = 0x100;
    this->arithmetic_unit = new ArithmeticUnit(this);
    this->logic_unit = new LogicUnit(this);
    this->shifting_unit = new ShiftingUnit(this);

    register_8bit_rotation_shifts_opcodes(this);
    register_16bit_arithmetic_opcodes(this);
    register_8bit_arithmetic_opcodes(this);
    register_jump_calls_opcodes(this);
    register_16bit_lsm_opcodes(this);
    register_8bit_lsm_opcodes(this);
    register_misc_opcodes(this);
}

uint16_t CPU::get_program_counter() const {
    return this->program_counter;
}

uint16_t CPU::get_stack_pointer() const {
    return this->stack_pointer;
}

uint8_t CPU::fetch_byte() const {
    return this->mmu[this->get_program_counter()];
}

uint8_t CPU::fetch_next_byte() {
    if (this->should_increment_pc)
        this->increment_pc();
    return this->fetch_byte();
}


uint16_t CPU::fetch_word() const {

    if (this->program_counter >= NUM_MEMORY_BYTES)
        return static_cast<uint16_t>(fetch_byte());

    uint8_t low_byte = this->mmu[this->program_counter];
    uint8_t high_byte = this->mmu[this->program_counter + 1];
    uint16_t word = (static_cast<uint16_t>(high_byte) << 8) + low_byte;
    return word;
}


uint16_t CPU::fetch_next_word() {
    uint8_t low_byte = fetch_next_byte();
    uint8_t high_byte = fetch_next_byte();
    uint16_t word = (static_cast<uint16_t>(high_byte) << 8) + low_byte;
    return word;
}

void CPU::fetch_cycle() {
    this->should_increment_pc = true;
    this->process_opcode();
    this->fetch_next_byte();
}


uint16_t CPU::next_opcode() const {
    uint8_t first_byte = this->fetch_byte();

    if (first_byte != 0xCB) {
        return first_byte;
    }

    if (this->program_counter >= NUM_MEMORY_BYTES)
        throw std::runtime_error("Rest of opcode out of bounds!");

    uint16_t second_byte = this->mmu[this->program_counter + 1];
    return (static_cast<uint16_t>(first_byte) << 8) + second_byte;
}

void CPU::process_opcode() {

    bool opcode_executed = false;
    for (std::vector<Opcode *>::iterator it = opcodes.begin(); it != opcodes.end() && !opcode_executed; it++) {
        uint16_t opcode_word = this->next_opcode();

        if ((*it)->should_execute(opcode_word)) {
            (*it)->execute(this);
            opcode_executed = true;
        }
    }

    if (!opcode_executed) {
        throw std::runtime_error("Could not find opcode!");
    }
}

void CPU::jump_to_address(uint16_t address) {
    this->program_counter = address;
    this->should_increment_pc = false;
}

void CPU::increment_pc() {
    this->increment_pc(1);
}

void CPU::increment_pc(uint16_t bytes_to_increment) {
    this->program_counter += bytes_to_increment;
}

void CPU::load_16bit_register_immediate(uint8_t reg_x, uint16_t value) {
    switch (reg_x) {
        case REGISTER_AF_INDEX:
            this->registers[REGISTER_A_INDEX] = static_cast<uint8_t>((value & 0xFF00) >> 8);
            this->registers[REGISTER_F_INDEX] = static_cast<uint8_t>(value & 0x00FF);
            break;
        case REGISTER_BC_INDEX:
            this->registers[REGISTER_B_INDEX] = static_cast<uint8_t>((value & 0xFF00) >> 8);
            this->registers[REGISTER_C_INDEX] = static_cast<uint8_t>(value & 0x00FF);
            break;
        case REGISTER_DE_INDEX:
            this->registers[REGISTER_D_INDEX] = static_cast<uint8_t>((value & 0xFF00) >> 8);
            this->registers[REGISTER_E_INDEX] = static_cast<uint8_t>(value & 0x00FF);
            break;
        case REGISTER_HL_INDEX:
            this->registers[REGISTER_H_INDEX] = static_cast<uint8_t>((value & 0xFF00) >> 8);
            this->registers[REGISTER_L_INDEX] = static_cast<uint8_t>(value & 0x00FF);
            break;
        case REGISTER_SP_INDEX:
            this->stack_pointer = value;
            break;
        default:
            throw std::runtime_error("16bit register index out of bounds!");
    }
}

void CPU::load_register_immediate(uint8_t reg_x, uint8_t value) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->registers[reg_x] = value;
}

void CPU::load_register_indirect(uint8_t reg_x, uint8_t reg_y) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    validate_leq_than<uint8_t>(reg_y, 0x08);
    this->registers[reg_x] = this->registers[reg_y];
}

void CPU::load_memory_indirect(uint8_t reg_x, uint16_t memory_address) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->registers[reg_x] = this->mmu[memory_address];
}

void CPU::store_memory_indirect(uint16_t memory_address, uint8_t reg_x) {
    validate_leq_than<uint8_t>(reg_x, 0x08);
    this->mmu[memory_address] = this->registers[reg_x];
}

void CPU::store_memory_immediate(uint16_t memory_address, uint8_t value) {
    this->mmu[memory_address] = value;
}

const uint8_t *CPU::get_registers() const {
    return this->registers;
}


uint16_t CPU::get_16bit_register(uint8_t index) const {
    switch (index) {
        case REGISTER_AF_INDEX:
            return ((static_cast<uint16_t>(this->registers[REGISTER_A_INDEX])) << 8) +
                   (static_cast<uint16_t>(this->registers[REGISTER_F_INDEX]));
        case REGISTER_BC_INDEX:
            return ((static_cast<uint16_t>(this->registers[REGISTER_B_INDEX])) << 8) +
                   (static_cast<uint16_t>(this->registers[REGISTER_C_INDEX]));
        case REGISTER_DE_INDEX:
            return ((static_cast<uint16_t>(this->registers[REGISTER_D_INDEX])) << 8) +
                   (static_cast<uint16_t>(this->registers[REGISTER_E_INDEX]));
        case REGISTER_HL_INDEX:
            return ((static_cast<uint16_t>(this->registers[REGISTER_H_INDEX])) << 8) +
                   (static_cast<uint16_t>(this->registers[REGISTER_L_INDEX]));
        case REGISTER_SP_INDEX:
            return this->stack_pointer;
        default:
            throw std::runtime_error("16bit register index out of bounds!");
    }
}


void CPU::call(uint16_t address) {
    this->push(this->get_program_counter() + 3);
    this->jump_to_address(address);
}

void CPU::push(uint16_t value) {
    this->mmu[--this->stack_pointer] = value & 0x00FF;
    this->mmu[--this->stack_pointer] = (value & 0xFF00) >> 8;
}

uint16_t CPU::peek() const {

    if (this->stack_pointer >= NUM_MEMORY_BYTES)
        throw std::runtime_error("Stack pointer out of bounds");

    uint16_t value = static_cast<uint16_t>(this->mmu[this->stack_pointer]) << 8;
    value += this->mmu[this->stack_pointer + 1];
    return value;

}

uint16_t CPU::pop() {
    uint16_t value = peek();
    this->stack_pointer += 2;
    return value;
}

void CPU::stop() {
    lcd_display_active = false;
    cpu_active = false;
}

void CPU::halt() {
    cpu_active = false;
}

void CPU::enable_interrupts() {
    interrupts_enabled = true;
}

void CPU::disable_interrupts() {
    interrupts_enabled = false;
}

void CPU::set_zero_flag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0x7F;
    this->registers[REGISTER_F_INDEX] |= (int(isOn) << 7);
}

void CPU::set_subtract_flag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xBF;
    this->registers[REGISTER_F_INDEX] |= (int(isOn) << 6);
}

void CPU::set_half_carry_flag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xDF;
    this->registers[REGISTER_F_INDEX] |= (int(isOn) << 5);
}

void CPU::set_carry_flag(bool isOn) {
    this->registers[REGISTER_F_INDEX] &= 0xEF;
    this->registers[REGISTER_F_INDEX] |= (int(isOn) << 4);
}

bool CPU::is_zero_flag_on() {
    return this->registers[REGISTER_F_INDEX] & (1 << 7);
}

bool CPU::is_subtract_flag_on() {
    return this->registers[REGISTER_F_INDEX] & (1 << 6);
}

bool CPU::is_half_carry_flag_on() {
    return this->registers[REGISTER_F_INDEX] & (1 << 5);
}

bool CPU::is_carry_flag_on() {
    return this->registers[REGISTER_F_INDEX] & (1 << 4);
}

ArithmeticUnit *CPU::get_arithmetic_unit() const {
    return arithmetic_unit;
}

LogicUnit *CPU::get_logic_unit() const {
    return logic_unit;
}

ShiftingUnit *CPU::get_shifting_unit() const {
    return shifting_unit;
}

bool CPU::is_lcd_display_active() const {
    return lcd_display_active;
}

bool CPU::is_cpu_active() const {
    return cpu_active;
}

uint8_t CPU::get_byte_memory_indirect(uint8_t reg_x) {
    return this->mmu[get_16bit_register(reg_x)];
}

uint16_t CPU::get_word_memory_indirect(uint8_t reg_x) {
    throw std::runtime_error("Not implemented"); // todo: do this
}

void CPU::register_opcode(const char *name, std::function<bool(uint16_t)> opcode_condition,
                          std::function<void(CPU *)> opcode_execution) {
    Opcode *opcode = new Opcode(name, opcode_condition, opcode_execution);
    this->opcodes.push_back(opcode);
}

CPU::~CPU() {
    for (std::vector<Opcode *>::iterator it = opcodes.begin(); it != opcodes.end(); it++) {
        delete *it;
    }
    delete[] registers;
    delete arithmetic_unit;
    delete logic_unit;
}

