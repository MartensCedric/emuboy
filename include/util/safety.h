//
// Created by cedric on 2021-06-17.
//

#ifndef EMUBOY_SAFETY_H
#define EMUBOY_SAFETY_H

template<typename T>
T validate_argument(T value, T mask)
{
    if((value & mask) != value)
        throw std::runtime_error("Value outside of mask!");

    return value;
}


#endif //EMUBOY_SAFETY_H
