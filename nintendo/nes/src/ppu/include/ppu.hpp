#ifndef PPU_H
#define PPU_H
#include <cstdint> 
#include "ppuState.hpp"
#include "ppuCharacterPage.hpp"
#include <functional>
#include <array>
#include "../../bus/include/pBus.hpp"

using namespace Gemunin::Nintendo::Nes::Comm;

namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Ppu{
                const int ScanlineCycleLength = 341;
                const int ScanlineEndCycle = 340;
                const int VisibleScanlines = 240;
                const int ScanlineVisibleDots = 256;
                const int FrameEndScanline = 261;

                const int AttributeOffset = 0x3C0;
                
                class PPU{
                    public:
                        PPU(PBus& bus);
                        void reset();
                        void step();
                    private:
                        PBus& pBus;
                        int cycle;
                        int scanline;
                        bool evenFrame;
                        bool vblank;
                        bool sprZeroHit;
                        bool spriteOverflow;
                        //Registers
                        uint16_t dataAddress;
                        uint16_t tempAddress;
                        uint8_t fineXScroll;
                        bool firstWrite;
                        uint8_t dataBuffer;

                        uint8_t spriteDataAddress;

                        //Setup flags and variables
                        bool longSprites;
                        bool generateInterrupt;
                        bool greyscaleMode;
                        bool showSprites;
                        bool showBackground;
                        bool hideEdgeSprites;
                        bool hideEdgeBackground;

                        PPUCharacterPage bgPage,sprPage;
                        uint16_t dataAddrIncrement;

                        std::vector<uint8_t> scanlineSprites;

                        PPUState pipelineState;
                        std::vector<uint8_t> spriteMemory;
                    //    std::vector<std::vector<sf::Color>> m_pictureBuffer;

                        //Functions
                        uint8_t read(uint16_t addr);
                };
            }
        }
    }
}


#endif