#ifndef CPU_H
#define CPU_H
#include "bus.hpp"

namespace Gemunin{
    namespace Nes8{
        namespace Cpu{
            class CPU{
                public:
                    CPU(Bus& bus);
                    ~CPU();
                    void reset();
                private:
                    Bus& bus;
                    uint8_t a,x,y,sp,status;
                    uint16_t pc;
            };
        }
    }
}
#endif