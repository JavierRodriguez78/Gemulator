#ifndef INTERRUPT_TYPE_H
#define INTERRUPT_TYPE_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Cpu{
                //INTERRUPTS IN NES https://www.nesdev.org/wiki/CPU_interrupts
                enum class InterruptType{
                    IRQ,
                    NMI,
                    BRK_
                };
            }
        }
    }
}
#endif