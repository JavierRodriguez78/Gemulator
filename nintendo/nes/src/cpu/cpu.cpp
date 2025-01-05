#include "include/cpu.hpp"
#include "include/addrMode2.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
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

                void CPU::skipPageCrossCycle(uint16_t a, uint16_t b)
                {
                    //Page is determined by the high byte
                    if ((a & 0xff00) != (b & 0xff00))
                    skipCycles += 1;
                };
                
                void CPU::setZN(uint8_t value)
                {   
                    fZ = !value;
                    fN = value & 0x80;
                };


                bool CPU::executeType2(uint8_t opCode){
                    if ((opCode & InstructionModeMask) == 2)
                    {
                        uint16_t location = 0;
                        auto op = static_cast<Operation2>((opCode & OperationMask) >> OperationShift);
                        auto addr_mode =static_cast<AddrMode2>((opCode & AddrModeMask) >> AddrModeShift);
                        switch (addr_mode)
                        {
                            case AddrMode2::Inmediate_:
                                location = rPC++;
                                break;
                            case AddrMode2::ZeroPage_:
                                location = bus.read(rPC++);
                                break;
                            case AddrMode2::Accumulator:
                                break;
                            case AddrMode2::Absolute_:
                                location = readAddress(rPC);
                                rPC += 2;
                                break;
                            case AddrMode2::Indexed:
                                {
                                    location = bus.read(rPC++);
                                    uint8_t index;
                                    if (op == Operation2::LDX || op == Operation2::STX)
                                        index = rY;
                                    else
                                        index = rX;
                                        //The mask wraps address around zero page
                                        location = (location + index) & 0xff;
                                }
                                break;
                            case AddrMode2::AbsoluteIndexed:
                                {
                                    location = readAddress(rPC);
                                    rPC += 2;
                                    uint8_t index;
                                    if (op == Operation2::LDX || op == Operation2::STX)
                                        index = rY;
                                    else
                                        index = rX;
                                        skipPageCrossCycle(location, location + index);
                                        location += index;
                                }
                                break;
                            default:
                                return false;
                    }

                    std::uint16_t operand = 0;
                    switch (op)
                    {       
                        case Operation2::ASL:
                        case Operation2::ROL:
                            if (addr_mode == AddrMode2::Accumulator)
                            {
                                auto prevC = fC;
                                fC = rA & 0x80;
                                rA <<= 1;
                                //If Rotating, set the bit-0 to the the previous carry
                                rA = rA | (prevC && (op == Operation2::ROL));
                                setZN(rA);
                            }
                            else
                            {
                                auto prevC = fC;
                                operand = bus.read(location);
                                fC = operand & 0x80;
                                operand = operand << 1 | (prevC && (op == Operation2::ROL));
                                setZN(operand);
                                bus.write(location, operand);
                            }
                            break;
                        case Operation2::LSR:
                        case Operation2::ROR:
                            if (addr_mode == AddrMode2::Accumulator)
                            {
                                auto prevC = fC;
                                fC = rA & 1;
                                rA >>= 1;
                                //If Rotating, set the bit-7 to the previous carry
                                 rA = rA | (prevC && (op == Operation2::ROR)) << 7;
                                setZN(rA);
                            }
                            else
                            {
                                auto prevC = fC;
                                operand = bus.read(location);
                                fC = operand & 1;
                                operand = operand >> 1 | (prevC && (op == Operation2::ROR)) << 7;
                                setZN(operand);
                                bus.write(location, operand);
                            }
                            break;
                        case Operation2::STX:
                            bus.write(location, rX);
                            break;
                        case Operation2::LDX:
                            rX = bus.read(location);
                            setZN(rX);
                            break;
                        case Operation2::DEC:
                        {
                            auto tmp = bus.read(location) - 1;
                            setZN(tmp);
                            bus.write(location, tmp);
                        }
                        break;
                        case Operation2::INC:
                        {   
                            auto tmp = bus.read(location) + 1;
                            setZN(tmp);
                            bus.write(location, tmp);
                        }
                        break;
                        default:
                            return false;
                    }
                    return true;
                    }   
                return false;
                };


                bool CPU::executeType1(uint8_t opCode){
                    uint16_t location = 0; //Location of the operand, could be in RAM
                    auto op = static_cast<Operation1>((opCode & OperationMask) >> OperationShift);
                    switch (static_cast<AddrMode1>(
                          (opCode & AddrModeMask) >> AddrModeShift))
                    {
                    
                        case AddrMode1::IndexedIndirectX:
                            {
                                uint8_t zero_addr = rX + bus.read(rPC++);
                                //Addresses wrap in zero page mode, thus pass through a mask
                                location = bus.read(zero_addr & 0xff) | bus.read((zero_addr + 1) & 0xff) << 8;
                            }
                            break;
                        case AddrMode1::ZeroPage:
                            location = bus.read(rPC++);
                            break;
                        case AddrMode1::Immediate:
                            location = rPC++;
                            break;
                        case AddrMode1::Absolute:
                            location = readAddress(rPC);
                            rPC += 2;
                            break;
                        case AddrMode1::IndirectY:
                            {
                                uint8_t zero_addr = bus.read(rPC++);
                                location = bus.read(zero_addr & 0xff) |bus.read((zero_addr + 1) & 0xff) << 8;
                                if (op != Operation1::STA)
                                    skipPageCrossCycle(location, location + rY);
                                    location += rY;
                            }
                            break;
                        case AddrMode1::IndexedX:
                            // Address wraps around in the zero page
                            location = (bus.read(rPC++) + rX) & 0xff;
                            break;
                        case AddrMode1::AbsoluteY:
                            location = readAddress(rPC);
                            rPC += 2;
                            if (op != Operation1::STA)
                                skipPageCrossCycle(location, location + rY);
                                location += rY;
                            break;
                        case AddrMode1::AbsoluteX:
                            location = readAddress(rPC);
                            rPC += 2;
                            if (op != Operation1::STA)
                                skipPageCrossCycle(location, location + rX);
                                location += rX;
                            break;
                        default:
                            return false;
                    };
                    
                    switch (op)
                    {
                        case Operation1::ORA:
                            rA |= bus.read(location);
                            setZN(rA);
                            break;
                        case Operation1::AND:
                            rA &= bus.read(location);
                            setZN(rA);
                            break;
                        case Operation1::EOR:
                            rA ^= bus.read(location);
                            setZN(rA);
                            break;
                        case Operation1::ADC:
                            {
                                uint8_t operand = bus.read(location);
                                std::uint16_t sum = rA + operand + fC;
                                //Carry forward or UNSIGNED overflow
                                fC = sum & 0x100;
                                //SIGNED overflow, would only happen if the sign of sum is
                                //different from BOTH the operands
                                fV = (rA ^ sum) & (operand ^ sum) & 0x80;
                                rA = static_cast<uint8_t>(sum);
                                setZN(rA);
                            }
                            break;
                        case Operation1::STA:
                            bus.write(location, rA);
                            break;
                        case Operation1::LDA:
                            rA = bus.read(location);
                            setZN(rA);
                            break;
                        case Operation1::SBC:
                            {
                                //High carry means "no borrow", thus negate and subtract
                                std::uint16_t subtrahend = bus.read(location),
                                diff = rA - subtrahend - !fC;
                                //if the ninth bit is 1, the resulting number is negative => borrow => low carry
                                fC = !(diff & 0x100);
                                //Same as ADC, except instead of the subtrahend,
                                //substitute with it's one complement
                                fV = (rA ^ diff) & (~subtrahend ^ diff) & 0x80;
                                rA = diff;
                                setZN(diff);
                            }
                            break;
                        case Operation1::CMP:
                            {
                                std::uint16_t diff = rA - bus.read(location);
                                fC = !(diff & 0x100);
                                setZN(diff);
                            }
                            break;
                        default:
                            return false;
                        }
                        return true;
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
}