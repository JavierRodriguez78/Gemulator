#include "include/mainWindow.hpp"
#include "include/dialogLog.hpp"
namespace Gemunin{
    namespace Editor{
        namespace Gui{
            MainWindow::MainWindow(EventManager& eventManager):eventManager(eventManager), dialogLog(eventManager){
                ImGui_ImplOpenGL3_NewFrame();
                ImGui_ImplSDL2_NewFrame();
              
            }
            void MainWindow::Draw(){
                ImGui::NewFrame();
            }
        }
    }
}