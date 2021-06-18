//
// Created by cedric on 2021-06-17.
//

#ifndef GAMEBOY_SAFETY_H
#define GAMEBOY_SAFETY_H

template<typename T>
T validate_argument(T value, T mask)
{
    if((value & mask) != value)
        throw std::runtime_error("Value outside of mask!");

    return value;
}


#endif //GAMEBOY_SAFETY_H
