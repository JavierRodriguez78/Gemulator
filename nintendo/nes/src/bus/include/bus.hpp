#ifndef BUS_H
#define BUS_H
#include <cstdint>
#include <vector>
#include <array>
#include <unordered_map>

#include "../../../core/src/logs/include/logger.hpp"
#include "../../../core/src/logs/include/logLevel.hpp"
#include "../../mappers/include/mapper.hpp"
#include "bIORegisters.hpp"


using namespace Gemunin::Nintendo::Nes::Mappers;
using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{

                struct IORegistersHasher
                {
                     std::size_t operator()(IORegisters const & reg) const noexcept
                     {
                         return std::hash<std::uint32_t>{}(reg);
                     }
                };
                    //Bus de la consola.
                    //Contiene la ram de 2 kb, la ram extra de 8 kb, y los registros de entrada y salida.
                    //Los registros de entrada y salida se encuentran en un espacio de memoria reservado para ellos.
                    //El resto de la memoria se encuentra reservada para la ram extra
                class Bus{
                    public:
                        Bus(Log& log);
                        void write(uint16_t addr, uint8_t value);
                        uint8_t read(uint16_t address);
                        bool setMapper(Log log, Mapper* mapper);
                    private:
                        // Extra RAM de 8 kb.
                        std::vector<uint8_t> extRAM;
                        // Ram de la CPU 2 kb
                        std::vector<uint8_t> ram;
                        //PGR ROM variable en tamañao.
                        std::vector<uint8_t> pgr_rom;
                        Log& log;
                        Mapper* mapper;

                        //Read Callback
                        std::unordered_map<IORegisters, std::function<uint8_t(void)>, IORegistersHasher> readCallbacks;;
                };
            }
        }
    }
}


#endif 