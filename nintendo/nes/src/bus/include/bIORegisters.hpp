#ifndef BUS_IO_REGISTERS_H
#define BUS_IO_REGISTERS_H

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                enum IORegisters{
                    PPUCTRL = 0x2000,
                    PPUMASK,
                    PPUSTATUS,
                    OAMADDR,
                    OAMDATA,
                    PPUSCROL,
                    PPUADDR,
                    PPUDATA,
                    OAMDMA = 0x4014,
                    JOY1 = 0x4016,
                    JOY2 = 0x4017
                };
            }
        }
    }
}

#endif