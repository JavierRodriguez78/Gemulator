#ifndef DIALOG_LOG_H
#define DIALOG_LOG_H

#include "imgui.h"
#include <string>
#include "../../../core/src/events/include/eventManager.hpp"
#include "../../../core/src/logs/include/logEvent.hpp"
#include "../../../core/src/logs/include/logger.hpp"

using namespace std;
using namespace Gemunin::Core::Events;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Editor{
        namespace Gui{
            class DialogLog{
                public:
                    DialogLog(EventManager& eventManager);
                    void Clear();
                    void AddLog(const std::string& message, Level level);
                    void AddText(const char * text);
                    void Draw(const char* title, bool* p_open);
                private:
                    struct LogEntry{
                        std::string message;
                        Level level;
                    };
                    bool autoScroll = true;
                    std::vector<LogEntry> logs;
            };
        }
    }
}
#endif