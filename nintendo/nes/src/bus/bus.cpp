#include "include/bus.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                Bus::Bus(Log& log): log(log){
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

                void Bus::write(uint16_t addr, uint8_t value){
                
                }

                bool Bus::setMapper(Log log, Mapper* mapper){
                    mapper = mapper;
                    if (!mapper)
                    {
                        log.AddLog("Mapper pointer is nullptr", Level::ERROR);
                        return false;
                    }

                    if (mapper->hasExtendedRAM())
                        extRAM.resize(0x2000);

                    return true;
                };
            }
        }
    }
}