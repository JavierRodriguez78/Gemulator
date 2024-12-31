#include "include/eventManager.hpp"
#include <string>
using namespace std;
namespace Gemunin{
    namespace Core{
        namespace Events{
            void EventManager::publish(const Event& event){
                  auto it = callbacks.find(event.getName());
                        if (it != callbacks.end()) {
                            for (const auto& callback : it->second) {
                                callback(event);
                            }
                        }
            }
            void EventManager::subscribe(const std::string& eventName, EventCallBack callback){
                callbacks[eventName].push_back(callback);
            }        
        }
    }
}