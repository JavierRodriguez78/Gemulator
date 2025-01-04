#ifndef ADDR_MODE_2_H
#define ADDR_MODE_2_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Cpu{
                enum class AddrMode2{
                    Inmediate_,
                    ZeroPage_,
                    Accumulator,
                    Absolute_,
                    Indexed         = 5,
                    AbsoluteIndexed = 7,
                };
            }
        }
    }
}

#endif