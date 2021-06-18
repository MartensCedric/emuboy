#include <iostream>
#include "util/safety.h"

int main() {

    validate_argument<uint16_t>(0xFF, 0x3);
    std::cout << "Hello, World!" << std::endl;
    return 0;
}
