#ifndef LOGGER_H
#define LOGGER_H
#include "../../events/include/eventManager.hpp"
#include "logEvent.hpp"
using namespace Gemunin::Core::Events;

namespace Gemunin{
    namespace Core{
        namespace Logs{
            enum Level{
                Info,
                Error
            };

            class Log{
                public:
                    Log(EventManager& eventmanager);
                    ~Log();
                    Level getLevel();
                    Log& setLevel(Level level);
                    void clear();
                    void AddLog(const std::string& message);
                    void Draw(const char* title, bool* p_open = nullptr);
                private:
                    Level logLevel;
                    EventManager& eventManager;
            };
        }
    }
};

#endif