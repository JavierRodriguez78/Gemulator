#include "include/window.hpp"
namespace Gemunin{
    namespace Editor{
        namespace Core{
            Window::Window(Graphic& graphic): graphic(graphic), io(io){
                IMGUI_CHECKVERSION();
                ImGui::CreateContext();
                io = ImGui::GetIO(); (void)io;
                ImGui::StyleColorsDark();
                // Configurar backends de ImGui
                ImGui_ImplSDL2_InitForOpenGL(graphic.getWindow(), graphic.getGLContext());
                ImGui_ImplOpenGL3_Init("#version 130");
            }

            ImGuiIO Window::getIo(){
                return io;
            };

            void Window::Render(){
                ImGui::Render();
                glViewport(0, 0, (int)this->io.DisplaySize.x, (int)this->io.DisplaySize.y);
                glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
                glClear(GL_COLOR_BUFFER_BIT);
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                SDL_GL_SwapWindow(graphic.getWindow());
            };

            Window::~Window(){
                ImGui_ImplOpenGL3_Shutdown();
                ImGui_ImplSDL2_Shutdown();
                ImGui::DestroyContext(); 
            }

        }
        
    }
}