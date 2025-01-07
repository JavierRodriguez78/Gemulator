#include"include/mapper.hpp"
#include "../../core/src/logs/include/logger.hpp"

using namespace Gemunin::Core::Logs;
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                std::unique_ptr<MapperType> Mapper::createMapper (MapperType mapper_t, Rom& cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb){
                    
                    std::unique_ptr<MapperType> ret(nullptr);
                    
                    switch (mapper_t)
                    {
                        default:
                            break;
                    }
                    return ret;
                };

                Mapper::~Mapper(){

                };
            }
        }
    }
}