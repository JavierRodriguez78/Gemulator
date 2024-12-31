#ifndef EVENT_H
#define EVENT_H

#include "string"

namespace Gemunin{
    namespace Core{
        namespace Events{
            class Event{
                public:
                    virtual ~Event() = default;
                    virtual std::string getName() const = 0;
            };
        }
    }
}

#endif