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

using namespace Gemunin::Editor::Gui;
using namespace Gemunin::Editor::Core;
using namespace Gemunin::Core::Graphics;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Core::Events;
using namespace Gemunin::Nintendo::Nes::Core;

int main(int argc, char* argv[]) {
    
    //Inicializar Graficos
    Graphic graphic;
    printf("Iniciando Gráficos\n");

    // Configurar ImGui
    Window window(graphic);
    printf("Inicando Gestor Ventanas\n");

    // Iniciando EventManager
    EventManager eventManager;
    printf("Iniciando el Gestor de Eventos\n");

    // Iniciando el Gestor de Logs.
    Log log(eventManager);
    printf("Iniciando el Gestor de Logs\n");

    // Main Frame
    MainWindow mainWindow(eventManager);
       printf("Iniciando la ventana Principal\n");
    
    //DialogLog
    DialogLog dialogLog(eventManager);
    bool show_dialog = true;
    
        
    //Iniciando Emulador de Nes    
    Nes nes(eventManager, log);
    nes.LoadRom("./nestest.nes");
   // nes.Reset();
   // nes.Start();
    
    // Main loop
    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
        }
        mainWindow.Draw();
        dialogLog.Draw("Console Logs", &show_dialog);
        // Renderizar
        window.Render();
    }
    return 0;
}