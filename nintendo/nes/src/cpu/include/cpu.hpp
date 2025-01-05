#ifndef CPU_H
#define CPU_H
#include "../../bus/include/bus.hpp"
#include "interruptType.hpp"
#include "addrMode1.hpp"
#include "addrMode2.hpp"
#include "operation0.hpp"
#include "operation1.hpp"
#include "operation2.hpp"

using namespace Gemunin::Nintendo::Nes::Comm;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
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
                        
                        int skipCycles;
                        int cycles;

                        //FUNCTIONS//
                        void setZeroNegative(uint8_t byte);
                        void interrupt(InterruptType interrupt);
                        bool executeType0(uint8_t opCode);
                        bool executeType1(uint8_t opCode);
                        bool executeType2(uint8_t opCode);
                        uint16_t readAddress(uint16_t addr);
                        //If a and b are in different pages, increases the m_SkipCycles by inc
                        void setPageCrossed(uint16_t a, uint16_t b, int inc);
                         //If a and b are in different pages, increases the m_SkipCycles by 1
                        void skipPageCrossCycle(uint16_t a, uint16_t b);
                        void setZN(uint8_t value);
                 };
            }
        }
    }
}
#endif