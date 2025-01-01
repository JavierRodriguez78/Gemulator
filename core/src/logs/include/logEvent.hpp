#ifndef LOG_EVENT_H
#define LOG_EVENT_H

#include "../../events/include/event.hpp"
#include "logger.hpp"
#include "logLevel.hpp"

using namespace Gemunin::Core::Events;


namespace Gemunin{
    namespace Core{
        namespace Logs{
            class LogEvent: public Event{
                public:
                    LogEvent();
                    LogEvent(const std::string& message, Level level);
                    std::string getName() const override;
                    std::string getMessage() const;
                    Level getLevel() const;
                private: 
                    std::string message;
                    Level level;
            };
        }
    }
}
#endif