#ifndef P_BUS_H
#define P_BUS_H
#include <vector>
#include <functional>
#include "../../mappers/include/mapper.hpp"
#include "../../mappers/include/nameTableMirroring.hpp"
#include "../../../core/src/logs/include/logger.hpp"
#include "../../../core/src/logs/include/logLevel.hpp"

using namespace Gemunin::Nintendo::Nes::Mappers;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                class PBus{
                    public:
                        PBus(Log& log);
                        bool setMapper(Mapper *mapper);
                        void updateMirroring();
                    private:
                        std::size_t NameTable0, NameTable1, NameTable2, NameTable3; //indices where they start in RAM vector
                        std::vector<uint8_t> palette;
                        std::vector<uint8_t> RAM;
                        Mapper* mapper;
                        Log& log;

                };
            }
        }
    }
}
#endif