#include "include/mainWindow.hpp"

namespace Gemunin{
    namespace Editor{
        namespace Gui{
            MainWindow::MainWindow(){
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
            }
            void MainWindow::Draw(){
                ImGui::NewFrame();
            }
        }
    }
}