#ifndef CARTRIDGE_H
#define CARTRIDGE_H
#include <string>
#include <vector>
#include <cstdint>
#include <stdint.h> 
#include "headerNes.hpp"
#include "../../../core/src/events/include/eventManager.hpp"
#include "../../../core/src/logs/include/logger.hpp"

using namespace Gemunin::Core::Events;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nes{
        namespace Cartridge{
            class Rom{
                public:
                    Rom(Log& log): log(log){};
                    bool loadRom(const std::string& filename);
                private:
                    Log& log;
                    std::vector<uint8_t> PRG_ROM;
                    std::vector<uint8_t> CHR_ROM;
            };
        }
    }
}

#endif