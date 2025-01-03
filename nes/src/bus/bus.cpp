#include "include/bus.hpp"

namespace Gemunin{
    namespace Nes8{
        namespace BusComm{
            Bus::Bus(){
                //Inicializamos la memoria.
                ram.fill(0);
            };

            uint8_t Bus::read(uint16_t address){
                //Mirroring de Ram.
                if (address < 0x2000) return ram[address % 0x0800];
                //PRG ROM
                if( address >= 0x8000) return pgr_rom[address - 0x8000];
                return 0;
            };
        }
    }
}