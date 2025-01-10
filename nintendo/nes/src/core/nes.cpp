#include "include/nes.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Core{
                Nes::Nes(EventManager& eventManager, Log& log):eventManager(eventManager), log(log), bus(log), pBus(log), rom(log), cpu(bus),ppu(pBus){
                    log.AddLog("Iniciando Nes",Gemunin::Core::Logs::Level::INFO );
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
                                        [&](){ pBus.updateMirroring(rom); });
                
                    if (!result_mapper)
                    {
                        log.AddLog("Mapper no soportado", Level::ERROR);    
                        return ;
                    }

                    if (!bus.setMapper(log, result_mapper.get()) ||
                        !pBus.setMapper(rom, result_mapper.get()))
                        return ;
                    
                    //Clean previus startup state
                    log.AddLog("Reset CPU", Level::INFO);
                    //cpu.reset();
                    //ppu.reset();
                    cpu.step();
                };
            }
        }
    }
}
