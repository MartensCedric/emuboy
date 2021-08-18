//
// Created by cedric on 2021-08-17.
//

#include <cstring>
#include <vector>
#include "cartridge/cartridge_loader.h"
#include "fstream"
#include "iostream"

uint8_t* load_cartridge(const char* filename)
{
    uint8_t* cartridge_bank_0 = new uint8_t[CARTRIDGE_SIZE];
    memset(cartridge_bank_0, 0, sizeof(cartridge_bank_0[0] * CARTRIDGE_SIZE));
    std::ifstream cartridge_file(filename, std::ios::binary);
    if(!cartridge_file.is_open())
        throw std::runtime_error("Could not open ROM: " + std::string(filename));

    std::vector<char> cartridge_contents((std::istreambuf_iterator<char>(cartridge_file)),
            std::istreambuf_iterator<char>());
    cartridge_file.close();
    if(cartridge_contents.size() > CARTRIDGE_SIZE)
        throw std::runtime_error("Cartridge size exceeds maximum size");
    std::copy(cartridge_contents.begin(), cartridge_contents.end(), cartridge_bank_0);
}