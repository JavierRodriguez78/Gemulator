#include "include/logger.hpp"
#include "../events/include/eventManager.hpp"


namespace Gemunin{
    namespace Core{
        namespace Logs{
            Log::Log(EventManager& eventManager): eventManager(eventManager){
               
            };

            Log& Log::setLevel(Level level){
                  Log::logLevel = level;
                  return *this;
            };

            Level Log::getLevel(){
                return Log::logLevel;
            }

            void Log::AddLog(const std::string& message){
                eventManager.publish(LogEvent(message));
            }

            Log::~Log(){

            };
        }
    }
}