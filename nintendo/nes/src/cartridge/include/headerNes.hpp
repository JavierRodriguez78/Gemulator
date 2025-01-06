#ifndef HEADER_NES_LOG
#define HEADER_NES_LOG
#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Cartridge{
                enum HeaderType{
                     v1=1,
                     v2   
                };
                struct iNesHeader{
                    char signature[4];      //Firma Nes [NES^Z] string
                    uint8_t prgRomChunks;   // PRG ROM size in 16KB units
                    uint8_t chrRomChunks;   // CHR ROM size in 8KB units
                    uint8_t flags6;         // Mapper, mirroring, battery, trainer
                    uint8_t flags7;         // Mapper, VS/Playchoice, NES 2.0
                    uint8_t PRG_RAM_Size;         // PRG RAM size (rarely used)
                    uint8_t TV_System;         // TV system (rarely used)
                    uint8_t flags10;        // TV system, PRG RAM presence (unofficial)
                    char padding[5];         // Unused padding
                };

                struct iNesHeader2{
                    char signature [4];
                    uint8_t prgRomChunksLSB;
                    uint8_t chrRomChunksLSB;
                    uint8_t flags6;
                    uint8_t flags7;
                    uint8_t mapperMSB;
                    uint8_t romMSB;
                    uint8_t PRG_RAM_Size;
                    uint8_t CHR_RAM_Size;
                    uint8_t TV_System;
                    uint8_t Vs_SystemType;
                    uint8_t MiscellaneousROMs;
                    uint8_t ExpansionDevice;
                };

                union iNesHeaderUnion{
                    iNesHeader v1;
                    iNesHeader2 v2;
                };
            }
        }
    }
}

#endif