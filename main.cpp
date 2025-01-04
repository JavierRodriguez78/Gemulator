#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "core/libs/gl3w/gl3w.h"
#include "editor/src/gui/include/mainWindow.hpp"
#include "editor/src/gui/include/dialogLog.hpp"
#include "editor/src/core/include/window.hpp"
#include "core/src/logs/include/logger.hpp"
#include "core/src/events/include/eventManager.hpp"
#include "core/src/graphics/include/graphic.hpp"
#include "nintendo/nes/src/core/include/nes.hpp"

using namespace Gemunin::Core::Graphics;
using namespace Gemunin::Editor::Gui;
using namespace Gemunin::Editor::Core;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Core::Events;
using namespace Gemunin::Nintendo::Nes::Core;

int main(int argc, char* argv[]) {
    
    //Inicializar Graficos
    Graphic graphic;

    // Configurar ImGui
    Window window(graphic);

    // Iniciando EventManager
    EventManager eventManager;
    bool show_dialog = true;
    Log log(eventManager);

    // Main Frame
    MainWindow mainWindow;

    DialogLog dialog(eventManager);

    //Iniciando Emulador de Nes    
    Nes nes(eventManager, log);
    nes.LoadRom("./nestest.nes");
    nes.Reset();
    nes.Start();
    
    // Main loop
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
        // Start the ImGui frame
        mainWindow.Draw();
       /* ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();*/
        dialog.Draw("Console Logs", &show_dialog);
        // Renderizar
        window.Render();
    }
    return 0;
}