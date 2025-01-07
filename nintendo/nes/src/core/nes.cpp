#include "include/nes.hpp"
#include "../cartridge/include/cartridge.hpp"
#include "../../core/src/logs/include/logger.hpp"
#include "../bus/include/bus.hpp"
#include "../cpu/include/cpu.hpp"
#include "../mappers/include/mapper.hpp"

using namespace Gemunin::Nintendo::Nes::Cartridge;
using namespace Gemunin::Nintendo::Nes::Cpu;
using namespace Gemunin::Core::Logs;
using namespace Gemunin::Nintendo::Nes::Comm;
using namespace Gemunin::Nintendo::Nes::Mappers;


namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Core{
                Nes::Nes(EventManager& eventManager, Log& log):eventManager(eventManager), log(log), cpu(cpu){
                    this->eventManager = eventManager;
                    log.AddLog("Iniciando Nes",Gemunin::Core::Logs::Level::INFO );
                    };


                bool Nes::LoadRom(const std::string& filename){
                    log.AddLog("Iniciando la carga del fichero-> "+ filename,Gemunin::Core::Logs::Level::INFO );
                    Rom rom(log);
                    rom.loadRom(filename);
                    uint8_t mapperId = rom.getMapper();
                    log.AddLog("mapper-> "+ std::to_string(mapperId),Gemunin::Core::Logs::Level::INFO );
                    
                    //Mapper::createMapper(static_cast<MapperType>(rom.getMapper()), rom);
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
                    log.AddLog("Iniciando la CPU", Gemunin::Core::Logs::Level::INFO);
                    CPU cpu(bus);
                };
            }
        }
    }
}
