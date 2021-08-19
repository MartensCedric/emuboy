//
// Created by cedric on 2021-08-18.
//

#ifndef EMUBOY_OPCODE_H
#define EMUBOY_OPCODE_H
#include <iostream>
#include <functional>
#include "CPU.h"
class Opcode
{
private:
    std::string name;
    std::function< bool(uint16_t)> opcode_condition;
    std::function<void (CPU*)> opcode_execution;
public:
    explicit Opcode(const char* name, std::function< bool(uint16_t)> opcode_condition, std::function<void (CPU*)> opcode_execution);
    bool should_execute(uint16_t target);
    void execute(CPU* cpu);
    ~Opcode();

};
#endif //EMUBOY_OPCODE_H
