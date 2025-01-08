#include "include/cartridge.hpp"


namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Cartridge{
                bool Rom::loadRom(const std::string& filename) {
                    
                    
                    //Carga del fichero.
                    std::ifstream romFile(filename, std::ios_base::in |std::ios::binary);
                    iNesHeaderUnion header;               
                    //Comprobamos si lo puede leer.
                    if (!romFile.is_open()) {
                        log.AddLog("Error en carga de ROM", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }
                    
                    //Comprobación de la cabecera
                    
                    romFile.read(reinterpret_cast<char*>(&header), sizeof(iNesHeader));
                    if (romFile.gcount() != sizeof(iNesHeader)) {
                        log.AddLog("Error leyendo la cabecera de  iNES.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }

                    //Comprobación de la firma.
                    // Verificar la firma
                    if (header.v1.signature[0] != 'N' || header.v1.signature[1] != 'E' || header.v1.signature[2] != 'S' || header.v1.signature[3] != 0x1A) {
                        log.AddLog("Cabecera inválida", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }


                    if ((header.v1.flags7 & 0x0C) ==0x08)
                        log.AddLog("La cabecera es iNes V2.0");
                        headerType= v2;
                        
                    if ((header.v1.flags7 & 0x0C) ==0x00)
                        log.AddLog("La cabecera es iNes V1.0");
                        headerType= v1;



                    // Calcular el tamaño de PRG ROM y CHR ROM
                    size_t prgSize = header.v1.prgRomChunks * 16384; // 16KB por chunk
                    size_t chrSize = header.v1.chrRomChunks * 8192;  // 8KB por chunk
                    size_t ramSize = 0;

                    if(headerType==v1){
                        this->mapperNumber= (header.v1.flags6 >> 4) | (header.v1.flags7 & 0xF0);

                        //Get PRG RAM Size if defined
                        if(header.v1.flags6 &0x02){
                            ramSize = header.v1.PRG_RAM_Size;
                            log.AddLog("PGRAM SIZE DEFINED: "+ std::to_string(ramSize), Gemunin::Core::Logs::Level::INFO);
                        }
                    }else if(headerType==v2){
                        prgSize = 16384 * header.v2.prgRomChunksLSB;  //TEMPORAL
                    };

                    // Leer PRG ROM
                    PRG_ROM.resize(prgSize);
                    romFile.read(reinterpret_cast<char*>(PRG_ROM.data()), prgSize);
                    if (romFile.gcount() != prgSize) {
                        log.AddLog("Error en la lecutra de la PRG ROM.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }
                    log.AddLog("PRG ROM size: " + std::to_string(header.v1.prgRomChunks) + " x 16KB",Gemunin::Core::Logs::Level::INFO);

                     // Leer CHR ROM
                    CHR_ROM.resize(chrSize);
                    romFile.read(reinterpret_cast<char*>(CHR_ROM.data()), chrSize);
                    if (romFile.gcount() != chrSize) {
                        log.AddLog("Error en la lecutra de CHR ROM.", Gemunin::Core::Logs::Level::ERROR);
                        return false;
                    }
                    
                    log.AddLog("CHR ROM size: " + std::to_string(header.v1.chrRomChunks) + " x 8KB", Gemunin::Core::Logs::Level::INFO);

                    //Carga completa
                    romFile.close();
                    log.AddLog("ROM loaded successfully!",Gemunin::Core::Logs::Level::INFO);
                    return true;
                };

                //Return ROM
                const std::vector<uint8_t>& Rom::getROM()
                {
                    log.AddLog("PRG_ROM returned", Gemunin::Core::Logs::Level::INFO);
                    return PRG_ROM;
                };
   
                // Return VROM
                 const std::vector<uint8_t>& Rom::getVROM(){
                    log.AddLog("CHR_ROM returned", Gemunin::Core::Logs::Level::INFO);
                    return CHR_ROM;
                 };

                //Return Mapper
                uint8_t Rom::getMapper(){
                     return this->mapperNumber;
                };

                //Return TableMirroring
                uint8_t Rom::getNameTableMirroring(){
                     return nameTableMirroring;
                };

                //Return if has extended RAM
                bool Rom::hasExtendedRAM()
                {
                    // Some ROMs don't have this set correctly, plus there's no particular reason to disable it.
                    return true;
                };
   
            }
        }
    }
}