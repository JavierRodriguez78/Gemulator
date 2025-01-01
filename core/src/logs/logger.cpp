#include <iomanip>
#include <sstream>
#include "include/logger.hpp"
#include "include/logLevel.hpp"
#include "../events/include/eventManager.hpp"
#include <chrono>

namespace Gemunin{
    namespace Core{
        namespace Logs{
            Log::Log(EventManager& eventManager): eventManager(eventManager){
               
            };
            void Log::AddLog(const std::string& message, Level level){
                std::string timestamp = getCurrentTime();
                std::ostringstream logMessage;
                logMessage << "[" << timestamp << "] [" << (level == Level::INFO ? "Info" : level == Level::WARNING ? "Warning" : "Error") << "] " << message;
                LogEvent logEvent(logMessage.str(), level);
                eventManager.publish(logEvent);
            }
            std::string Log::getCurrentTime() {
                auto now = std::chrono::system_clock::now();
                std::time_t now_c = std::chrono::system_clock::to_time_t(now);
                std::tm now_tm = *std::localtime(&now_c);

                std::ostringstream oss;
                oss << std::put_time(&now_tm, "%Y-%m-%d %H:%M:%S");
                return oss.str();
            }
            Log::~Log(){

            };
        }
    }
}