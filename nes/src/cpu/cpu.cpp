#include "include/cpu.hpp"

namespace Gemunin{
    namespace Nes8{
        namespace Cpu{
            CPU::CPU(Bus& bus): bus(bus){
                reset();
            }

            //Reset CPU
            void CPU::reset(){
                pc=0x8000;
                sp=0xFD;
                a=x=y=0;
                status= 0x34;
            }
        }
    }
}