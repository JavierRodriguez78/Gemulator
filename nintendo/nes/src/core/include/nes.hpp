#ifndef NES_H
#define NES_H

#include "../../core/src/events/include/eventManager.hpp"
#include "../../core/src/logs/include/logger.hpp"
#include "../../cpu/include/cpu.hpp"
#include "../../ppu/include/ppu.hpp"
#include "../../bus/include/bus.hpp"
#include "../../bus/include/pBus.hpp"
#include "../../cartridge/include/cartridge.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
using namespace Gemunin::Nintendo::Nes::Cpu;
using namespace Gemunin::Nintendo::Nes::Ppu;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Nintendo::Nes::Comm;
using namespace Gemunin::Nintendo::Nes::Mappers;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Core{
                class Nes{
                    public:
                        Nes(EventManager& eventmanager, Log& log);
                        bool LoadRom(const std::string& filename);
                        bool Reset();
                        void Run();
                    private:
                        std::unique_ptr<Mapper> result_mapper;
                        EventManager& eventManager;
                        Rom rom;
                        Log& log;
                        Bus bus;
                        PBus pBus;
                        CPU cpu;
                        PPU ppu;
                };
            }
        }
    }
}
#endif