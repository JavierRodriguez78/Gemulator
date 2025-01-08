#ifndef MAPPER_MMC3_H
#define MAPPER_MMC3_H
#include "../../cartridge/include/cartridge.hpp"
#include "mapper.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                class MapperMMC3ROM: public Mapper{
                    public:
                        MapperMMC3ROM();
                        MapperMMC3ROM(Rom &cart, std::function<void()> interrupt_cb, std::function<void(void)> mirroring_cb);  
                        uint8_t readPRG(uint16_t addr);
                    private:
                        uint32_t targetRegister;
                        bool prgBankMode;
                        bool chrInversion;

                        uint32_t bankRegister[8];

                        bool irqEnabled;
                        uint8_t irqCounter;
                        uint8_t irqLatch;
                        bool irqReloadPending;

                        std::vector<uint8_t> prgRam;
                        std::vector<uint8_t> mirroringRam;
                        const uint8_t *prgBank0;
                        const uint8_t *prgBank1;
                        const uint8_t *prgBank2;
                        const uint8_t *prgBank3;

                        std::array<uint32_t, 8> chrBanks;

                        NameTableMirroring mirroring;
                        std::function<void(void)> mirroringCallback;
                        std::function<void()> interruptCallback;
                };
            }
        }
    }
}

#endif