#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"

namespace Gemunin{
    namespace Editor{
        namespace Gui{
            class MainWindow{
                public:
                    MainWindow();
                    void Draw();
                private:
            };
        }
    }
}

#endif