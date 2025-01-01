#include "include/logEvent.hpp"
#include "include/logLevel.hpp"

namespace Gemunin{
    namespace Core{
        namespace Logs{


            LogEvent::LogEvent(const std::string& message, Gemunin::Core::Logs::Level level) : message(message), level(level) {}

            std::string LogEvent::getName()const {
                return "LogEvent";
            };
            
            std::string LogEvent::getMessage() const{
                return message;
            };

            Level LogEvent::getLevel() const{
                return level;
            }
        }
    }
}