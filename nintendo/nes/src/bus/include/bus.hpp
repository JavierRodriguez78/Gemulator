#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <vector>
#include <array>

#include "../../../core/src/logs/include/logger.hpp"
#include "../../../core/src/logs/include/logLevel.hpp"
#include "../../mappers/include/mapper.hpp"


using namespace Gemunin::Nintendo::Nes::Mappers;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                class Bus{
                    public:
                        Bus(Log& log);
                        void write(uint16_t addr, uint8_t value);
                        uint8_t read(uint16_t address);
                        bool setMapper(Log log, Mapper* mapper);
                    private:
                        // Extra RAM de 8 kb.
                        std::vector<uint8_t> extRAM;
                        // Ram de la CPU 2 kb
                        std::array<uint8_t, 2048> ram;
                        //PGR ROM variable en tamañao.
                        std::vector<uint8_t> pgr_rom;
                        Log& log;
                };
            }
        }
    }
}


#endif 