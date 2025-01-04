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

        }
        
    }
}