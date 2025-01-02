#ifndef HEADER_NES_LOG
#define HEADER_NES_LOG
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

namespace Gemunin{
    namespace Nes8{
        namespace Cartridge{
            struct iNesHeader{
                char signature[4];      //Firma Nes [NES^Z] string
                uint8_t prgRomChunks;   // PRG ROM size in 16KB units
                uint8_t chrRomChunks;   // CHR ROM size in 8KB units
                uint8_t flags6;         // Mapper, mirroring, battery, trainer
                uint8_t flags7;         // Mapper, VS/Playchoice, NES 2.0
                uint8_t flags8;         // PRG RAM size (rarely used)
                uint8_t flags9;         // TV system (rarely used)
                uint8_t flags10;        // TV system, PRG RAM presence (unofficial)
                char unused[5];         // Unused padding
            };
        }
    }
}

#endif