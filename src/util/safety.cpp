//
// Created by cedric on 2021-06-17.
//
#include <stdexcept>
#include "util/safety.h"

template<typename T>
T validate_argument(T value, T mask)
{
    if((value & mask) != value)
        throw std::runtime_error("Value outside of mask!");

    return value;
}
