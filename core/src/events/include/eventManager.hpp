#ifndef EVENT_MANAGER_H
#define EVENT_MANAGER_H

#include "string"
#include <functional>
#include "event.hpp"
#include <unordered_map>
#include <vector>

namespace Gemunin{
    namespace Core{
        namespace Events{
            class EventManager{
                public:
                    using EventCallBack = std::function<void(const Event&)>;
                    void subscribe(const std::string& eventName, EventCallBack callback);
                    void publish(const Event& event);
                private:
                    std::unordered_map<std::string, std::vector<EventCallBack>> callbacks;
            };
        }
    }
}

#endif