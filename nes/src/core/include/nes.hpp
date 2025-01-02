#ifndef NES_H
#define NES_H
#include "../../core/src/events/include/eventManager.hpp"
#include "../../core/src/logs/include/logger.hpp"

using namespace Gemunin::Core::Events;
using namespace Gemunin::Core::Logs;
namespace Gemunin{
    namespace Nes8{
        namespace Core{
            class Nes{
                public:
                    Nes(EventManager& eventmanager);
                    bool LoadRom(const std::string& filename);
                private:
                    EventManager& eventManager;
            };
        }
    }
}
#endif