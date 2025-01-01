#ifndef LOGGER_H
#define LOGGER_H
#include "../../events/include/eventManager.hpp"
#include "logEvent.hpp"
#include "logLevel.hpp"
using namespace Gemunin::Core::Events;

namespace Gemunin{
    namespace Core{
        namespace Logs{
            class Log{
                public:
                    Log(EventManager& eventmanager);
                    ~Log();
                    void clear();
                    void AddLog(const std::string& message, Level level = Gemunin::Core::Logs::Level::INFO);
                private:
                    EventManager& eventManager;
                    std::string getCurrentTime();
            };
        }
    }
};

#endif