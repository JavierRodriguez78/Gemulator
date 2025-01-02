#include "include/cartridge.hpp"
#include "../../../core/src/logs/include/logger.hpp"

using namespace Gemunin::Core::Logs;

namespace Gemunin{
    namespace Nes8{
        namespace Cartridge{
                bool Rom::loadRom(const std::string& filename) {
                    
                    //Carga del fichero.
                    std::ifstream romFile(filename, std::ios::binary);
                    if (!romFile.is_open()) {
                        log.AddLog("Error en carga de ROM", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }

                    //Comprobación de la cabecera
                    iNesHeader header;
                    romFile.read(reinterpret_cast<char*>(&header), sizeof(iNesHeader));
                    if (romFile.gcount() != sizeof(iNesHeader)) {
                        log.AddLog("Error leyendo la cabecera de  iNES.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }

                    //Comprobación de la firma.
                    // Verificar la firma
                    if (header.signature[0] != 'N' || header.signature[1] != 'E' || header.signature[2] != 'S' || header.signature[3] != 0x1A) {
                        log.AddLog("Cabecera inválida", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }

                    // Calcular el tamaño de PRG ROM y CHR ROM
                    size_t prgSize = header.prgRomChunks * 16384; // 16KB por chunk
                    size_t chrSize = header.chrRomChunks * 8192;  // 8KB por chunk



                    // Leer PRG ROM
                    PRG_ROM.resize(prgSize);
                    romFile.read(reinterpret_cast<char*>(PRG_ROM.data()), prgSize);
                    if (romFile.gcount() != prgSize) {
                        log.AddLog("Error en la lecutra de la PRG ROM.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }
                    log.AddLog("PRG ROM size: " + std::to_string(header.prgRomChunks) + " x 16KB",Gemunin::Core::Logs::Level::INFO);

                     // Leer CHR ROM
                    CHR_ROM.resize(chrSize);
                    romFile.read(reinterpret_cast<char*>(CHR_ROM.data()), chrSize);
                    if (romFile.gcount() != chrSize) {
                        log.AddLog("Error en la lecutra de CHR ROM.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }
                    
                    log.AddLog("CHR ROM size: " + std::to_string(header.chrRomChunks) + " x 8KB", Gemunin::Core::Logs::Level::INFO);

                    //Carga completa
                    log.AddLog("ROM loaded successfully!",Gemunin::Core::Logs::Level::INFO);
       
     


                    return true;
                };

        }
    }
}