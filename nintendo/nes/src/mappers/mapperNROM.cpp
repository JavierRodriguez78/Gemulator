#include "include/mapperNROM.hpp"
#include "include/mapper.hpp"
#include "include/mapperType.hpp"
#include "../cartridge/include/cartridge.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{

                //Create NROM
                MapperNROM::MapperNROM(Rom &cart, Log& log):Mapper(cart,MapperType::NROM,log),log(log){
                    
                    if (cart.getROM().size() == 0x4000) //1 bank
                    {
                        oneBank = true;
                    }else //2 banks
                    {
                        oneBank = false;
                    }

                    if (cart.getVROM().size() == 0)
                    {
                        usesCharacterRAM = true;
                        characterRAM.resize(0x2000);
                        log.AddLog("Uses CharacterRam", Gemunin::Core::Logs::Level::INFO);
                    }
                    else
                        usesCharacterRAM = false;
                };

                //Read PROGRAM NROM
                uint8_t MapperNROM::readPRG(uint16_t addr){
                    if (!oneBank)
                        return cartridge.getROM()[addr - 0x8000];
                    else //mirrored
                        return cartridge.getROM()[(addr - 0x8000) & 0x3fff];
                }

                //Write PROGRAM 
                void MapperNROM::writePRG (uint16_t addr, uint8_t value){
                    log.AddLog("ROM memory write attempt at: "+std::to_string(addr)+" to set " +std::to_string(value), Gemunin::Core::Logs::Level::INFO);
                };

                // Read CHR Rom
                uint8_t MapperNROM::readCHR(uint16_t addr)
                {
                    if (usesCharacterRAM)
                        return characterRAM[addr];
                    else
                        return cartridge.getVROM()[addr];
                };
                //Write CHR Rom
                void MapperNROM::writeCHR(uint16_t addr, uint8_t value){
                    
                    if (usesCharacterRAM)
                        characterRAM[addr] = value;
                    else
                        log.AddLog("Read-only CHR memory write attempt at "+std::to_string(addr) );
                }
            }
        }
    }
}