#include "include/nes.hpp"
#include "../cartridge/include/cartridge.hpp"
#include "../../core/src/logs/include/logger.hpp"
#include "../cpu/include/bus.hpp"
#include "../cpu/include/cpu.hpp"

using namespace Gemunin::Nes8::Cartridge;
using namespace Gemunin::Nes8::Cpu;
using namespace Gemunin::Core::Logs;


namespace Gemunin{
    namespace Nes8{
        namespace Core{
            Nes::Nes(EventManager& eventManager, Log& log):eventManager(eventManager), log(log), cpu(cpu){
                this->eventManager = eventManager;
                log.AddLog("Iniciando Nes",Gemunin::Core::Logs::Level::INFO );
                };


            bool Nes::LoadRom(const std::string& filename){
                log.AddLog("Iniciando la carga del fichero-> "+ filename,Gemunin::Core::Logs::Level::INFO );
                Rom rom(log);
                rom.loadRom(filename);
               return true;
            };

            bool Nes::Reset(){
                log.AddLog("Reiniciando el Core", Gemunin::Core::Logs::Level::INFO);
                return true;
            };

            void Nes::Start(){
                log.AddLog("Iniciando el Bus", Gemunin::Core::Logs::Level::INFO);
                Bus bus;
                this->bus = bus;
                CPU cpu(bus);
            };
        }
    }
}
