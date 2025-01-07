#ifndef NES_H
#define NES_H

#include "../../core/src/events/include/eventManager.hpp"
#include "../../core/src/logs/include/logger.hpp"
#include "../../cpu/include/cpu.hpp"
#include "../../bus/include/bus.hpp"
#include "../../bus/include/pBus.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
using namespace Gemunin::Nintendo::Nes::Cpu;
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
                        void Start();
                    private:
                        std::unique_ptr<Mapper> mapper;
                        EventManager& eventManager;
                        Log& log;
                        Bus bus;
                        PBus pBus;
                        CPU& cpu;
                };
            }
        }
    }
}
#endif