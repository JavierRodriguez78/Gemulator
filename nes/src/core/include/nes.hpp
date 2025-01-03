#ifndef NES_H
#define NES_H
#include "../../core/src/events/include/eventManager.hpp"
#include "../../core/src/logs/include/logger.hpp"
#include "../../cpu/include/cpu.hpp"
#include "../../bus/include/bus.hpp"

using namespace Gemunin::Core::Events;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Nes8::Cpu;
using namespace Gemunin::Nes8::BusComm;

namespace Gemunin{
    namespace Nes8{
        namespace Core{
            class Nes{
                public:
                    Nes(EventManager& eventmanager, Log& log);
                    bool LoadRom(const std::string& filename);
                    bool Reset();
                    void Start();
                private:
                    EventManager& eventManager;
                    Log& log;
                    Bus bus;
                    CPU& cpu;
            };
        }
    }
}
#endif