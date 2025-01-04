#ifndef ADDR_MODE_1_H
#define ADDR_MODE_1_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Cpu{
                enum class AddrMode1{
                    IndexedIndirectX,
                    ZeroPage,
                    Immediate,
                    Absolute,
                    IndirectY,
                    IndexedX,
                    AbsoluteY,
                    AbsoluteX,
                };
            }
        }
    }
}
#endif