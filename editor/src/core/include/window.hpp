#ifndef WINDOW_H
#define WINDOW_H
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "../../../core/src/graphics/include/graphic.hpp"

using namespace Gemunin::Core::Graphics;

namespace Gemunin{
    namespace Editor{
        namespace Core{
            class Window{
                public:
                    Window(Graphic& graphic);
                    ImGuiIO getIo();
                private:
                    Graphic& graphic;
                    ImGuiIO io;
            };
        }
    }
}
#endif