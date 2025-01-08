#include "include/ppu.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Ppu{
                PPU::PPU(PBus& pBus): pBus(pBus){
                    reset();
                };
                void PPU::reset(){
                    longSprites = generateInterrupt = greyscaleMode = vblank = spriteOverflow = false;
                    showBackground = showSprites = evenFrame = firstWrite = true;
                    bgPage = sprPage = PPUCharacterPage::Low;
                    dataAddress = cycle = scanline = spriteDataAddress = fineXScroll = tempAddress = 0;
                    dataAddrIncrement = 1;
                    pipelineState = PPUState::PreRender;
                    scanlineSprites.reserve(8);
                    scanlineSprites.resize(0);
                };
            }
        }
    }
}