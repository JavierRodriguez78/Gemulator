#ifndef DIALOG_LOG_H
#define DIALOG_LOG_H

#include "imgui.h"
#include <string>
#include "../../../core/src/events/include/eventManager.hpp"
#include "../../../core/src/logs/include/logEvent.hpp"

using namespace std;
using namespace Gemunin::Core::Events;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Editor{
        namespace Gui{
            class DialogLog{
                public:
                    DialogLog(EventManager& eventManager);
                    void Show(bool* open);
                    void Clear();
                    void AddLog(const std::string& message);
                    void AddText(const char * text);
                    void Draw(const char* title, bool* p_open);
                private:
                   bool autoScroll = true;
                   std::vector<std::string> logs;
            };
        }
    }
}
#endif