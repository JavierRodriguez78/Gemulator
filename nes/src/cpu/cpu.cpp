#include "include/cpu.hpp"
#include "include/addrMode2.hpp"

namespace Gemunin{
    namespace Nes8{
        namespace Cpu{

            const auto InstructionModeMask = 0x3;
            const auto AddrModeMask = 0x1c;
            const auto AddrModeShift = 2;
            const auto OperationMask = 0xe0;
            const auto OperationShift = 5;
            
            CPU::CPU(Bus& bus): bus(bus){
                reset();
            };

            CPU::~CPU(){

            };


            //Reset CPU
            void CPU::reset(){
                //Limpiando los contadores de ciclo 
                cycles=skipCycles=0;
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

            bool CPU::executeType0(uint8_t opCode){
                if ((opCode & InstructionModeMask) == 0x0)
                {
                    uint16_t location = 0;
                    switch (static_cast<AddrMode2>((opCode & AddrModeMask) >> AddrModeShift)){
                        case AddrMode2::Inmediate_ :
                            location = rPC++;
                            break;
                        case AddrMode2::ZeroPage_:
                            location = bus.read(rPC++);
                            break;
                        case AddrMode2::Absolute_:
                            location = readAddress(rPC++);
                            rPC +=2;
                            break;
                        case AddrMode2::Indexed:
                            // Address wraps around in the zero page
                            location = (bus.read(rPC++) + rX) & 0xff;
                            break;
                        case AddrMode2::AbsoluteIndexed:
                            location = readAddress(rPC);
                            rPC +=2;
                            setPageCrossed(location, location +rX, 0);
                            location +=rX;
                            break;
                        default:
                            return false;
                    };
                    std::uint16_t operand = 0;
                    switch (static_cast<Operation0>((opCode & OperationMask) >> OperationShift)){
                        
                        default:
                        return false;                        
                    };
                };
                return false;
            };

            uint16_t CPU::readAddress(uint16_t address){
                return bus.read(address) | bus.read(address + 1) << 8;
            };

            void CPU::setPageCrossed(uint16_t a, uint16_t b, int inc){
                 //La págian se determina por el byte más alto.
                if ((a & 0xff00) != (b & 0xff00))
                    skipCycles += inc;
            };

        }
    }
}