#ifndef CPU_H
#define CPU_H
#include "bus.hpp"
#include "interruptType.hpp"

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
                    //Registers
                    uint8_t rA,rX,rY,rSP,rStatus;
                    uint16_t rPC;
                    //Status Flags
                    bool fC, fZ,fI,fD,fV,fN;
                    //Pending execute Interrupts
                    bool pendingNMI;
                    bool pendingIRQ;
                    
                    //FUNCTIONS//
                    void setZeroNegative(uint8_t byte);
                    void interrupt(InterruptType interrupt);
            };
        }
    }
}
#endif