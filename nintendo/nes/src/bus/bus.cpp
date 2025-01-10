#include "include/bus.hpp"

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Comm{
                Bus::Bus(Log& log): log(log),
                    //Inicializamos la memoria.
                    ram(0x800, 0),
                    mapper(nullptr)
                    {};

                uint8_t Bus::read(uint16_t address){
                    log.AddLog("Read Access Bus Atempt: "+ std::to_string(address), Level::INFO);
                    //Mirroring de Ram.
                  /*  if (address < 0x2000) {
                        log.AddLog("Read Address Atempt <0x2000: "+ std::to_string(address), Level::INFO);
                        return ram[address % 0x7ff];
                    } else if( address < 0x4020)
                    {
                        log.AddLog("Read Address Atempt <0x4020: "+ std::to_string(address), Level::INFO);
                        
                        if (address < 0x4000) //PPU
                        {
                            
                            auto it = readCallbacks.find(static_cast<IORegisters>(address & 0x2007));
                            if ( it != readCallbacks.end())
                                return it->second();
                            else
                                log.AddLog("No Callback Registered for I/O register at: "+address, Level::WARNING);
                        }
                        else if(address<0x4018 && address >= 0x4014)
                        {
                            auto it = readCallbacks.find(static_cast<IORegisters>(address));
                            if( it!=readCallbacks.end())
                                return it->second();
                            else
                                log.AddLog("No Callback Registered for I/O register at: "+address, Level::WARNING);
                        }
                        else
                            log.AddLog("Read Access Atempt: "+address, Level::WARNING);
                            
                        }  
                        else if (address < 0x6000)
                        {
                            log.AddLog("Expansion ROM read ateempted. This is currently unsupported: "+address, Level::WARNING);
                            
                        }
                         else if (address < 0x8000)
                        { 
                            if (mapper->hasExtendedRAM())
                            {
                                return extRAM[address - 0x6000];
                            }
                        }
                        else {
                            return mapper->readPRG(address);
                        };*/
                        log.AddLog("No ha entrado en ninguna "+ std::to_string(address), Level::INFO);
                       return 0;
                        
                }; 
                    
                

                void Bus::write(uint16_t addr, uint8_t value){
                
                }

                bool Bus::setMapper(Log log, Mapper* mapper){
                    mapper = mapper;
                    if (!mapper)
                    {
                        log.AddLog("Mapper pointer is nullptr", Level::ERROR);
                        return false;
                    }

                    if (mapper->hasExtendedRAM())
                        extRAM.resize(0x2000);

                    return true;
                };
            }
        }
    }
}