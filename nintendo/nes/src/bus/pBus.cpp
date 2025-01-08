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
                void PBus::updateMirroring(){
                    switch (mapper->getNameTableMirroring())
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

                bool PBus::setMapper(Mapper *mapper)
                {
                    if (!mapper)
                    {
                        log.AddLog("Mapper argument is nullptr", Level::ERROR);
                        return false;
                    }
                    mapper = mapper;
                   // updateMirroring();
                    return true;
                }
            }
        }
    }
}