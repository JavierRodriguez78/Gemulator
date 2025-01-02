#include "include/nes.hpp"
#include "../cartridge/include/cartridge.hpp"

using namespace Gemunin::Nes8::Cartridge;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nes8{
        namespace Core{
            Nes::Nes(EventManager& eventManager):eventManager(eventManager){
               
            };
            bool Nes::LoadRom(const std::string& filename){
                Log log(eventManager);
                log.AddLog("Iniciando la carga del fichero-> "+ filename,Gemunin::Core::Logs::Level::INFO );
                Rom rom(log);
                rom.loadRom(filename);
               return true;
            };
        }
    }
}
