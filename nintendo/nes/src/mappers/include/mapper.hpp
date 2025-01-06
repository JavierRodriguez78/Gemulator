#ifndef MAPPER_H
#define MAPPER_H
#include <memory>
#include <functional>
#include "nameTableMirroring.hpp"
#include "mapperType.hpp"
#include "../../cartridge/include/cartridge.hpp"
#include "../../../core/src/logs/include/logger.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
using namespace Gemunin::Core::Logs;


namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                class Mapper{
                    public:
                        Mapper(Rom& cart, MapperType t, Log& log) : cartridge(cart), type(t), log(log) {};
                        ~Mapper();
                       // static std::unique_ptr<MapperType> createMapper (MapperType mapper_t, Rom& cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb);
                    private:
                        Log& log;
                        Rom& cartridge;
                        MapperType type;
                };
            }
        }
    }
}

#endif