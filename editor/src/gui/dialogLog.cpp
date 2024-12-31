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
                    AddLog(logEvent.getMessage());
                });
            };
            
            void DialogLog::Show(bool *open){
                if (*open) {
                    ImGui::Begin("Console Logs", open);
                    if (ImGui::Button("Close")) {
                        *open = false;
                    }
                ImGui::End();
                }
            }
            
            void DialogLog::AddLog(const std::string& message){
                logs.push_back(message);
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
                    ImGui::TextUnformatted(log.c_str());
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
