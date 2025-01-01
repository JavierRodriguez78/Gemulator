#include <SDL2/SDL.h>
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include "editor/libs/gl3w/gl3w.h"
#include "editor/src/gui/include/dialogLog.hpp"
#include "core/src/logs/include/logger.hpp"
#include "core/src/events/include/eventManager.hpp"

using namespace Gemunin::Editor::Gui;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Core::Events;

int main(int argc, char* argv[]) {
    // Inicializar SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Crear ventana SDL con contexto OpenGL
    SDL_Window* window = SDL_CreateWindow("Gemunin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    SDL_MaximizeWindow(window);
    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Inicializar gl3w
    if (gl3wInit()) {
        printf("Failed to initialize OpenGL loader!\n");
        return -1;
    }

    // Configurar ImGui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();

    // Configurar backends de ImGui
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init("#version 130");

    EventManager eventManager;
    bool show_dialog = true;
    DialogLog dialog(eventManager);
    Log log(eventManager);
    log.AddLog("INICIANDO EL SISTEMA",Gemunin::Core::Logs::Level::INFO);
    log.AddLog("EJEMPLO DE WARN",Gemunin::Core::Logs::Level::WARNING);
    log.AddLog("EJEMPLO DE ERROR",Gemunin::Core::Logs::Level::ERROR);
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

        SDL_GL_SwapWindow(window);
    }

    // Limpiar
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();
    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}