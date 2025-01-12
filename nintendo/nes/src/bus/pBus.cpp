#include "include/pBus.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                //Creando objeto
                PBus::PBus(Log& log):
                    palette(0x20),
                    RAM(0x800),
                    mapper(nullptr),log(log){};

                //Actualizando Mirroring.
                void PBus::updateMirroring(Rom cartridge_){
                    if (!mapper)
                    {
                        log.AddLog("Mapper is nullptr", Level::ERROR);
                        return;
                    }
                   switch (mapper->getNameTableMirroring(cartridge_))
                    {
                        case NameTableMirroring::Horizontal:
                            NameTable0 = NameTable1 = 0;
                            NameTable2 = NameTable3 = 0x400;
                            log.AddLog("Horizontal Name Table mirroring set. (Vertical Scrolling)",Level::INFO);
                            break;
                        case NameTableMirroring::Vertical:
                            NameTable0 = NameTable2 = 0;
                            NameTable1 = NameTable3 = 0x400;
                            log.AddLog("Vertical Name Table mirroring set. (Horizontal Scrolling)",Level::INFO);
                            break;
                        case NameTableMirroring::OneScreenLower:
                            NameTable0 = NameTable1 = NameTable2 = NameTable3 = 0;
                            log.AddLog("Single Screen mirroring set with lower bank.", Level::INFO);
                            break;
                        case NameTableMirroring::OneScreenHigher:
                            NameTable0 = NameTable1 = NameTable2 = NameTable3 = 0x400;
                            log.AddLog("Single Screen mirroring set with higher bank.", Level::INFO);
                            break;
                        case NameTableMirroring::FourScreen:
                            NameTable0 = RAM.size();
                            log.AddLog( "FourScreen mirroring.", Level::INFO);
                            break;
                        default:
                            NameTable0 = NameTable1 = NameTable2 = NameTable3 = 0;
                            log.AddLog("Unsupported Name Table mirroring",Level::INFO);
                    }
                };

                bool PBus::setMapper(Rom cartridge_, Mapper *mapper_)
                {
                    if (!mapper_)
                    {
                        log.AddLog("Mapper argument is nullptr", Level::ERROR);
                        return false;
                    }
                    mapper = mapper_;
                    log.AddLog("Set Mapper to " + std::to_string(reinterpret_cast<uintptr_t>(mapper)), Level::INFO);
                    updateMirroring(cartridge_);
                    return true;
                };
                void PBus::scanlineIRQ(){
                       mapper->scanlineIRQ();
                };

                uint8_t PBus::read(uint16_t addr)
                {
                    // PictureBus is limited to 0x3fff
                    addr = addr & 0x3fff;
                    if (addr < 0x2000)
                    {
                        return mapper->readCHR(addr);
                    }
                    else if (addr <= 0x3eff)
                    {
                        const auto index = addr & 0x3ff;
                        // Name tables upto 0x3000, then mirrored upto 3eff
                        auto normalizedAddr = addr;
                        if (addr >= 0x3000)
                        {
                            normalizedAddr -= 0x1000;
                        }

                        if (NameTable0 >= RAM.size())
                            return mapper->readCHR(normalizedAddr);
                        else if (normalizedAddr < 0x2400)      //NT0
                            return RAM[NameTable0 + index];
                        else if (normalizedAddr < 0x2800) //NT1
                            return RAM[NameTable1 + index];
                        else if (normalizedAddr < 0x2c00) //NT2
                            return RAM[NameTable2 + index];
                        else /* if (normalizedAddr < 0x3000)*/ //NT3
                        return RAM[NameTable3 + index];
                    }
                    else if (addr <= 0x3fff)
                    {
                        auto paletteAddr = addr & 0x1f;
                        return readPalette(paletteAddr);
                    }
                    return 0;
                };

                uint8_t PBus::readPalette(uint8_t paletteAddr){
                    // Addresses $3F10/$3F14/$3F18/$3F1C are mirrors of $3F00/$3F04/$3F08/$3F0C
                    if (paletteAddr >= 0x10 && paletteAddr % 4 == 0) {
                        paletteAddr = paletteAddr & 0xf;
                    }
                    return palette[paletteAddr];
                };
            }
        }
    }
}