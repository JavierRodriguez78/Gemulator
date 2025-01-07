#include "include/nes.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Core{
                Nes::Nes(EventManager& eventManager, Log& log):eventManager(eventManager), log(log), cpu(cpu), pBus(pBus){
                    log.AddLog("Iniciando Nes",Gemunin::Core::Logs::Level::INFO );
                    this->eventManager = eventManager;
                    Bus bus;
                    CPU cpu(bus);
                };


                bool Nes::LoadRom(const std::string& filename){
                    log.AddLog("Iniciando la carga del fichero-> "+ filename,Gemunin::Core::Logs::Level::INFO );
                    Rom rom(log);
                    rom.loadRom(filename);
                    uint8_t mapperId = rom.getMapper();
                    log.AddLog("mapper-> "+ std::to_string(mapperId),Gemunin::Core::Logs::Level::INFO );
                   /* mapper=Mapper::createMapper(static_cast<MapperType>(rom.getMapper()),
                                        rom,
                                        [&](){ cpu.interrupt(InterruptType::IRQ); },
                                        [&](){ pBus.updateMirroring(); });*/

                    return true;
                };

                bool Nes::Reset(){
                    log.AddLog("Reiniciando el Core", Gemunin::Core::Logs::Level::INFO);
                    return true;
                };

                void Nes::Start(){
                    log.AddLog("Iniciando la consola", Gemunin::Core::Logs::Level::INFO);
                };
            }
        }
    }
}
