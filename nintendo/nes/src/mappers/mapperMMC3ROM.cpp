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

                uint8_t MapperMMC3ROM::readPRG(uint16_t addr)
                {
                  /*  if (addr >= 0x6000 && addr <= 0x7FFF)
                    {
                        return  prgRam[addr & 0x1fff];
                    }
                    if (addr >= 0x8000 && addr <= 0x9FFF)
                    {
                        return *(prgBank0 + (addr & 0x1fff));
                    }

                    if (addr >= 0xA000 && addr <= 0xBFFF)
                    {
                        return   *(prgBank1 + (addr & 0x1fff));
                    }

                    if (addr >= 0xC000 && addr <= 0xDFFF)
                    {
                        return *(prgBank2 + (addr & 0x1fff));
                    }

                    if (addr >= 0xE000)
                    {
                        return *(prgBank3  +  (addr & 0x1fff));
                    }*/

                return 0;       
             

                };
            };

            void MapperMMC3ROM::scanlineIRQ(){
                bool zeroTransition = false;
                if (irqCounter == 0 || irqReloadPending)
                {
                    irqCounter = irqLatch;
                    // zeroTransition = m_irqReloadPending;
                    irqReloadPending = false;
                }
                else
                {
                    irqCounter--;
                    zeroTransition = irqCounter == 0;
                }   
                if(zeroTransition && irqEnabled)
                {
                    interruptCallback();
                }
            };
             
            uint8_t MapperMMC3ROM::readCHR(uint16_t addr)
            {
                if (addr < 0x1fff)
                {
                    // select 1kb bank
                    const auto bankSelect = addr >> 10;
                    // get the configured base address for the bank
                    const auto baseAddress = chrBanks[bankSelect];
                    const auto offset = addr & 0x3ff;
                    return cartridge.getVROM()[baseAddress + offset];
                }
                else if (addr <= 0x2fff)
                {
                    return mirroringRam[addr-0x2000];
                }

                return 0;
            };
        }
    }
}