#include "include/mapperMMC3ROM.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{

                //Create MMC3
                MapperMMC3ROM::MapperMMC3ROM(Rom &cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb) :
                    Mapper(cart, MapperType::MMC3),
                    targetRegister(0),
                    prgBankMode(false),
                    chrInversion(false),
                    bankRegister{},
                    irqEnabled(false),
                    irqCounter(0),
                    irqLatch(0),
                    irqReloadPending(false),
                    prgRam(32 * 1024),
                    mirroringRam(4 * 1024),
                    mirroring(NameTableMirroring::Horizontal),
                    mirroringCallback(mirroring_cb),
                    interruptCallback(interrupt_cb)
                {
                    prgBank0 = &cart.getROM()[cart.getROM().size() - 0x4000];
                    prgBank1 = &cart.getROM()[cart.getROM().size() - 0x2000];
                    prgBank2 = &cart.getROM()[cart.getROM().size() - 0x4000];
                    prgBank3 = &cart.getROM()[cart.getROM().size() - 0x2000];


                    for (auto& bank: chrBanks)
                    {
                        bank = cart.getVROM().size() - 0x400;
                    }
                    chrBanks[0] = cart.getVROM().size() - 0x800;
                    chrBanks[3] = cart.getVROM().size() - 0x800;
                };

            }
        }
    }
}