//
// Created by cedric on 2021-08-17.
//

#ifndef EMUBOY_CARTRIDGE_LOADER_H
#define EMUBOY_CARTRIDGE_LOADER_H
#include "cstdint"

#define CARTRIDGE_BANK_0 0
#define CARTRIDGE_BANK_1 1

#define CARTRIDGE_SIZE 0x4000

uint8_t* load_cartridge(const char* filename);
#endif //EMUBOY_CARTRIDGE_LOADER_H
