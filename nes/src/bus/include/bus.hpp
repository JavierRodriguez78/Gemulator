#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <vector>
#include <array>

namespace Gemunin{
    namespace Nes8{
        namespace BusComm{
            class Bus{
                public:
                    Bus();
                    void write(uint16_t addr, uint8_t value);
                    uint8_t read(uint16_t address);
                private:
                    // Ram de la CPU 2 kb
                    std::array<uint8_t, 2048> ram;
                    //PGR ROM variable en tamañao.
                    std::vector<uint8_t> pgr_rom;
            };
        }
    }
}


#endif 