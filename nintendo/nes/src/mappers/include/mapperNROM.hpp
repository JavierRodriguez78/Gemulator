#ifndef MAPPER_NROM_H
#define MAPPER_NROM_H
#include "mapper.hpp"


namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                class MapperNROM: public Mapper{
                    public:
                        MapperNROM(Rom cart);
                        uint8_t readPRG(uint16_t addr);
                        void writePRG (uint16_t addr, uint8_t value);
                        uint8_t readCHR(uint16_t addr);
                        void writeCHR(uint16_t addr, uint8_t value);

                    private:
                        bool oneBank;
                        bool usesCharacterRAM;
                        std::vector<uint8_t> characterRAM;
                };
            }
        }
    }
}

#endif