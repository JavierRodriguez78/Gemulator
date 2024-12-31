#include "include/logEvent.hpp"

namespace Gemunin{
    namespace Core{
        namespace Logs{
            LogEvent::LogEvent(){};
            std::string LogEvent::getName()const {
                return "LogEvent";
            };
            std::string LogEvent::getMessage() const{
                return message;
            };
        }
    }
}