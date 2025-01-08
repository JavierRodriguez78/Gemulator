#ifndef MAPPER_H
#define MAPPER_H
#include <memory>
#include <functional>
#include "nameTableMirroring.hpp"
#include "mapperType.hpp"
#include "../../cartridge/include/cartridge.hpp"


using namespace Gemunin::Nintendo::Nes::Cartridge;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                class Mapper{
                    public:
                        Mapper();
                        Mapper(Rom cartridge,  MapperType t) : cartridge(cartridge), type(t) {};
                        static std::unique_ptr<Mapper> createMapper (MapperType mapper_t, Rom& cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb);
                        virtual NameTableMirroring getNameTableMirroring();
                    protected:
                        Rom& cartridge;
                        MapperType type;
                };
            }
        }
    }
}

#endif