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

template <typename T>
T validate_leq_than(T value, T target)
{
    if(value > target)
        throw std::runtime_error("Value larger than target!");

    return value;
}


#endif //EMUBOY_SAFETY_H
