#include"include/mapper.hpp"
#include "include/mapperNROM.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{

                std::unique_ptr<Mapper> Mapper::createMapper (MapperType mapper_t, Rom& cartridge, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb){
                    
                    std::unique_ptr<Mapper> ret(nullptr);
                    switch (mapper_t)
                    {
                        case MapperType::NROM:
                            
                           ret.reset(new MapperNROM(cartridge));
                           
                            break;
                        default:
                            break;
                    }
                    return ret;
                };

                NameTableMirroring Mapper::getNameTableMirroring(){
                    return static_cast<NameTableMirroring>(cartridge.getNameTableMirroring());
                };
            }
        }
    }
}