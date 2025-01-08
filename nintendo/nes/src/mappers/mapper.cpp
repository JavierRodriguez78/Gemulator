#include"include/mapper.hpp"
#include "include/mapperNROM.hpp"
#include "include/mapperMMC3ROM.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{

                std::unique_ptr<Mapper> Mapper::createMapper (Log log,MapperType mapper_t, Rom& cartridge, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb){
                    
                    std::unique_ptr<Mapper> ret(nullptr);
                    switch (mapper_t)
                    {
                        case MapperType::NROM:
                           log.AddLog("Creando Mapper NROM", Level::INFO);
                           ret.reset(new MapperNROM(cartridge));
                           break;
                      
                        case MapperType::MMC3:
                            log.AddLog("Creando Mapper MMC3", Level::INFO);             
                            ret.reset(new MapperMMC3ROM(cartridge, interrupt_cb, mirroring_cb));
                            break;
                        
                        default:
                            break;
                    }
                    return ret;
                    
                };

                NameTableMirroring Mapper::getNameTableMirroring(Rom cartridge_){
                    uint8_t mirroring = cartridge_.getNameTableMirroring();
                    return static_cast<NameTableMirroring>(cartridge_.getNameTableMirroring());
                };
               
            }
        }
    }
}