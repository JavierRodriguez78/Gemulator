#include "include/dialogLog.hpp"
#include "imgui.h"
#include <iostream>


namespace Gemunin{
    namespace Editor{
        namespace Gui{
            DialogLog::DialogLog(EventManager& eventManager){
                printf("Iniciando Dialog Log\n");
                eventManager.subscribe("LogEvent", [this](const Event& event){
                    const LogEvent& logEvent =static_cast<const LogEvent&>(event);
                    AddLog(logEvent.getMessage(), logEvent.getLevel());
                });
            };
            
            void DialogLog::AddLog(const std::string& message, Level level){
                logs.push_back({message, level});
            }

            void DialogLog::Clear(){
                logs.clear();
            }
            void DialogLog::Draw(const char* title, bool* p_open){
                 if (!ImGui::Begin(title, p_open)) {
                    ImGui::End();
                    return;
                }
                 if (ImGui::Button("Clear")) {
                     Clear();
                }
                ImGui::SameLine();
                bool copy_to_clipboard = ImGui::Button("Copy");
                ImGui::SameLine();
                ImGui::Checkbox("Auto-scroll", &autoScroll);
                ImGui::Separator();

                ImGui::BeginChild("Log", ImVec2(0, 0), false, ImGuiWindowFlags_AlwaysVerticalScrollbar);

                if (copy_to_clipboard) {
                    ImGui::LogToClipboard();
                }
           
                for (const auto& log : logs) {
                    ImVec4 color;
                    switch (log.level) {
                        case Gemunin::Core::Logs::Level::INFO: color = ImVec4(1.0f, 1.0f, 1.0f, 1.0f); break;
                        case Gemunin::Core::Logs::Level::WARNING: color = ImVec4(1.0f, 1.0f, 0.0f, 1.0f); break;
                        case Gemunin::Core::Logs::Level::ERROR:   color = ImVec4(1.0f, 0.0f, 0.0f, 1.0f); break;
                    }
                    ImGui::TextColored(color, "%s", log.message.c_str());
                }
            
                if (autoScroll && ImGui::GetScrollY() >= ImGui::GetScrollMaxY()) {
                    ImGui::SetScrollHereY(1.0f);
                }
                
                ImGui::EndChild();
                ImGui::End();
            }

            void DialogLog::AddText(const char * text){
                ImGui::Text(text);
            }
        }
    }
}
