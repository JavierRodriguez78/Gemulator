#include"include/mapper.hpp"

using namespace Gemunin::Core::Logs;
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{

                std::unique_ptr<Mapper> Mapper::createMapper (MapperType mapper_t, Rom& cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb){
                    
                    std::unique_ptr<Mapper> ret(nullptr);

                                        
                    
                    switch (mapper_t)
                    {
                        case MapperType::NROM:
                            ret.reset(new MapperNROM(cart));
                        break;
                        default:
                            break;
                    }
                    return ret;
                };

                NameTableMirroring Mapper::getNameTableMirroring(){
                    return static_cast<NameTableMirroring>(cartridge.getNameTableMirroring());
                };

                Mapper::~Mapper(){

                };


            }
        }
    }
}