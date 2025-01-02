#include "include/cpu.hpp"

namespace Gemunin{
    namespace Nes8{
        namespace Cpu{
            CPU::CPU(Bus& bus): bus(bus){
                reset();
            };

            CPU::~CPU(){

            };

            
            //Reset CPU
            void CPU::reset(){
                
                //Limpiando registros
                rPC=0x8000;
                rSP=0xFD;
                rA=rX=rY=0;
                rStatus= 0x34;
                //Limpiando Flags
                fI= true;
                fC=fD=fN=fV=fZ = false;
            };

            //Set Zero negative flags.
            void CPU::setZeroNegative(uint8_t byte){
                fZ = !byte;
                fN = byte & 0x80;
            };

            //Ejecución de interupciones.
            void CPU::interrupt(InterruptType interrupt){
                switch(interrupt){
                    case InterruptType::NMI:
                        pendingNMI = true;
                        break;
                    case InterruptType::IRQ:
                        pendingIRQ = true;
                        break;
                    default:
                        break;
                };
            };
        }
    }
}