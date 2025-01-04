#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../../../core/src/events/include/eventManager.hpp"
#include "dialogLog.hpp"

using namespace Gemunin::Core::Events;

namespace Gemunin{
    namespace Editor{
        namespace Gui{
            class MainWindow{
                public:
                    MainWindow(EventManager& eventManager);
                    void Draw();
                private:
                   EventManager& eventManager;
                   DialogLog dialogLog;
            };
        }
    }
}

#endif