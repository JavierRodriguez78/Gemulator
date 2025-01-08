#include "include/nes.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Core{
                Nes::Nes(EventManager& eventManager, Log& log):eventManager(eventManager), log(log), cpu(cpu),bus(log), pBus(log), rom(log){
                    log.AddLog("Iniciando Nes",Gemunin::Core::Logs::Level::INFO );
                    this->eventManager = eventManager;
                    Bus bus(log);
                    PBus pBus(log);
                    Rom rom(log);
                    CPU cpu(bus);
                };


                bool Nes::LoadRom(const std::string& filename){
                    log.AddLog("Iniciando la carga del fichero-> "+ filename,Gemunin::Core::Logs::Level::INFO );
                    rom.loadRom(filename);
                    uint8_t mapperId = rom.getMapper();
                    log.AddLog("mapper-> "+ std::to_string(mapperId),Gemunin::Core::Logs::Level::INFO );
                    return true;
                };

                bool Nes::Reset(){
                    log.AddLog("Reiniciando la consola", Gemunin::Core::Logs::Level::INFO);
                    return true;
                };

                void Nes::Run(){
                    log.AddLog("Iniciando la consola", Gemunin::Core::Logs::Level::INFO);
                    result_mapper = Mapper::createMapper(log, static_cast<MapperType>(rom.getMapper()),
                                        rom,
                                        [&](){ cpu.interrupt(InterruptType::IRQ); },
                                        [&](){ pBus.updateMirroring(); });
                
                    if (!result_mapper)
                    {
                        log.AddLog("Mapper no soportado", Level::ERROR);    
                        return ;
                    }

                    if (!bus.setMapper(log, result_mapper.get()) ||
                        !pBus.setMapper(result_mapper.get()))
                        return ;
                };
            }
        }
    }
}
