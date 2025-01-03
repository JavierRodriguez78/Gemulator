#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "core/libs/gl3w/gl3w.h"
#include "editor/src/gui/include/dialogLog.hpp"
#include "core/src/logs/include/logger.hpp"
#include "core/src/events/include/eventManager.hpp"
#include "core/src/graphics/include/graphic.hpp"
#include "nes/src/core/include/nes.hpp"

using namespace Gemunin::Core::Graphics;
using namespace Gemunin::Editor::Gui;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Core::Events;
using namespace Gemunin::Nes8::Core;

int main(int argc, char* argv[]) {
    
    //Inicializar Graficos
    Graphic graphic;

    // Configurar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Configurar backends de ImGui
    ImGui_ImplSDL2_InitForOpenGL(graphic.getWindow(), graphic.getGLContext());
    ImGui_ImplOpenGL3_Init("#version 130");

    EventManager eventManager;
    bool show_dialog = true;
    DialogLog dialog(eventManager);
    Log log(eventManager);
    log.AddLog("INICIANDO EL SISTEMA",Gemunin::Core::Logs::Level::INFO);
    log.AddLog("EJEMPLO DE WARN",Gemunin::Core::Logs::Level::WARNING);
    log.AddLog("EJEMPLO DE ERROR",Gemunin::Core::Logs::Level::ERROR);

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
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        dialog.Draw("Console Logs", &show_dialog);
        // Renderizar
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        SDL_GL_SwapWindow(graphic.getWindow());
    }

    // Limpiar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    return 0;
}