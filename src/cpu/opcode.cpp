//
// Created by cedric on 2021-08-18.
//

#include "cpu/opcode.h"

#include <utility>

Opcode::Opcode(const char* name, std::function<bool(uint16_t)> opcode_condition, std::function<void (CPU*)> opcode_execution) : name(std::string(name)), opcode_condition(std::move(opcode_condition)), opcode_execution(std::move(opcode_execution)){

}

bool Opcode::should_execute(uint16_t target) {
    return this->opcode_condition(target);
}

void Opcode::execute(CPU* cpu) {
    std::cout << name << std::endl;
    this->opcode_execution(cpu);
}

Opcode::~Opcode() {

}
