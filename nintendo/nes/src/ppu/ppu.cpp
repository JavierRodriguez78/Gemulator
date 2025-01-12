#include "include/ppu.hpp"
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Ppu{
                PPU::PPU(PBus& pBus): pBus(pBus){
                   
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

                void PPU::step(){
                    switch(pipelineState){
                        case PPUState::PreRender:
                            if (cycle == 1)
                                vblank = sprZeroHit = false;
                            else if (cycle == ScanlineVisibleDots + 2 && showBackground && showSprites)
                            {
                                //Set bits related to horizontal position
                                dataAddress &= ~0x41f; //Unset horizontal bits
                                dataAddress |= tempAddress & 0x41f; //Copy
                            }
                            else if (cycle > 280 && cycle <= 304 && showBackground && showSprites)
                            {
                                //Set vertical bits
                                dataAddress &= ~0x7be0; //Unset bits related to horizontal
                                dataAddress |= tempAddress & 0x7be0; //Copy
                            }
                            //   if (m_cycle > 257 && m_cycle < 320)
                            //                     m_spriteDataAddress = 0;
                            //if rendering is on, every other frame is one cycle shorter
                            if (cycle >= ScanlineEndCycle - (!evenFrame && showBackground && showSprites))
                            {
                                pipelineState = PPUState::Render;
                                cycle = scanline = 0;
                            }
                            // add IRQ support for MMC3
                            if(cycle==260 && showBackground && showSprites){
                                pBus.scanlineIRQ();
                            }
                            break;

                        case PPUState::Render:
                            if (cycle > 0 && cycle <= ScanlineVisibleDots)
                            {
                                uint8_t bgColor = 0, sprColor = 0;
                                bool bgOpaque = false, sprOpaque = true;
                                bool spriteForeground = false;

                                int x = cycle - 1;
                                int y = scanline;

                                if (showBackground)
                                {
                                    auto x_fine = (fineXScroll + x) % 8;
                                    if (!hideEdgeBackground || x >= 8)
                                    {
                                        //fetch tile
                                        auto addr = 0x2000 | (dataAddress & 0x0FFF); //mask off fine y
                                        //auto addr = 0x2000 + x / 8 + (y / 8) * (ScanlineVisibleDots / 8);
                                        uint8_t tile = read(addr);
                                        //fetch pattern
                                        //Each pattern occupies 16 bytes, so multiply by 16
                                        addr = (tile * 16) + ((dataAddress >> 12/*y % 8*/) & 0x7); //Add fine y
                                        addr |= static_cast<int>(bgPage) << 12; //set whether the pattern is in the high or low page
                                        //Get the corresponding bit determined by (8 - x_fine) from the right
                                        bgColor = (read(addr) >> (7 ^ x_fine)) & 1; //bit 0 of palette entry
                                        bgColor |= ((read(addr + 8) >> (7 ^ x_fine)) & 1) << 1; //bit 1
                                        bgOpaque = bgColor; //flag used to calculate final pixel with the sprite pixel
                                        //fetch attribute and calculate higher two bits of palette
                                        addr = 0x23C0 | (dataAddress & 0x0C00) | ((dataAddress >> 4) & 0x38)
                                        | ((dataAddress >> 2) & 0x07);
                                        auto attribute = read(addr);
                                        int shift = ((dataAddress >> 4) & 4) | (dataAddress & 2);
                                        //Extract and set the upper two bits for the color
                                        bgColor |= ((attribute >> shift) & 0x3) << 2;
                                    }
                                    //Increment/wrap coarse X
                                    if (x_fine == 7)
                                    {
                                        if ((dataAddress & 0x001F) == 31) // if coarse X == 31
                                        {
                                            dataAddress &= ~0x001F;          // coarse X = 0
                                            dataAddress ^= 0x0400;           // switch horizontal nametable
                                        }
                                        else
                                        {
                                            dataAddress += 1;                // increment coarse X
                                        }
                                    }
                                }

                                if (showSprites && (!hideEdgeSprites || x >= 8))
                                {
                                    for (auto i : scanlineSprites)
                                    {
                                        uint8_t spr_x = spriteMemory[i * 4 + 3];
                                        if (0 > x - spr_x || x - spr_x >= 8)
                                        continue;

                                    uint8_t spr_y     = spriteMemory[i * 4 + 0] + 1,
                                    tile      = spriteMemory[i * 4 + 1],
                                    attribute = spriteMemory[i * 4 + 2];

                                    int length = (longSprites) ? 16 : 8;

                                    int x_shift = (x - spr_x) % 8, y_offset = (y - spr_y) % length;

                                    if ((attribute & 0x40) == 0) //If NOT flipping horizontally
                                        x_shift ^= 7;
                                    if ((attribute & 0x80) != 0) //IF flipping vertically
                                        y_offset ^= (length - 1);
                                    uint16_t addr = 0;
                                    if (!longSprites)
                                    {
                                        addr = tile * 16 + y_offset;
                                        if (sprPage == PPUCharacterPage::High) addr += 0x1000;
                                    }
                                    else //8x16 sprites
                                    {
                                        //bit-3 is one if it is the bottom tile of the sprite, multiply by two to get the next pattern
                                        y_offset = (y_offset & 7) | ((y_offset & 8) << 1);
                                        addr = (tile >> 1) * 32 + y_offset;
                                        addr |= (tile & 1) << 12; //Bank 0x1000 if bit-0 is high
                                    }
                                    sprColor |= (read(addr) >> (x_shift)) & 1; //bit 0 of palette entry
                                    sprColor |= ((read(addr + 8) >> (x_shift)) & 1) << 1; //bit 1
                                    if (!(sprOpaque = sprColor))
                                    {
                                        sprColor = 0;
                                        continue;
                                    }
                                    sprColor |= 0x10; //Select sprite palette
                                    sprColor |= (attribute & 0x3) << 2; //bits 2-3
                                    spriteForeground = !(attribute & 0x20);
                                    //Sprite-0 hit detection
                                    if (!sprZeroHit && showBackground && i == 0 && sprOpaque && bgOpaque)
                                    {
                                        sprZeroHit = true;
                                    }

                                    break; //Exit the loop now since we've found the highest priority sprite
                                }
                            }
                            uint8_t paletteAddr = bgColor;
                            if ( (!bgOpaque && sprOpaque) ||
                            (bgOpaque && sprOpaque && spriteForeground) )
                                paletteAddr = sprColor;
                            else if (!bgOpaque && !sprOpaque)
                                paletteAddr = 0;
                            //else bgColor
                           // pictureBuffer[x][y] = sf::Color(colors[PBus.readPalette(paletteAddr)]);
                        }
                        else if (cycle == ScanlineVisibleDots + 1 && showBackground)
                        {
                            //Shamelessly copied from nesdev wiki
                            if ((dataAddress & 0x7000) != 0x7000)  // if fine Y < 7
                                dataAddress += 0x1000;              // increment fine Y
                            else
                            {
                                dataAddress &= ~0x7000;             // fine Y = 0
                                int y = (dataAddress & 0x03E0) >> 5;    // let y = coarse Y
                                if (y == 29)
                                {
                                    y = 0;                                // coarse Y = 0
                                    dataAddress ^= 0x0800;              // switch vertical nametable
                                }
                                else if (y == 31)
                                    y = 0;                                // coarse Y = 0, nametable not switched
                        else
                            y += 1;                               // increment coarse Y
                            dataAddress = (dataAddress & ~0x03E0) | (y << 5);
                                                                // put coarse Y back into m_dataAddress
                        }
                    }
                    else if (cycle == ScanlineVisibleDots + 2 && showBackground && showSprites)
                    {
                        //Copy bits related to horizontal position
                        dataAddress &= ~0x41f;
                        dataAddress |= tempAddress & 0x41f;
                    }

                    //                 if (m_cycle > 257 && m_cycle < 320)
                    //                     m_spriteDataAddress = 0;

                    // add IRQ support for MMC3
                    if(cycle==260 && showBackground && showSprites){
                        pBus.scanlineIRQ();
                    }
                    if (cycle >= ScanlineEndCycle)
                    {
                        //Find and index sprites that are on the next Scanline
                        //This isn't where/when this indexing, actually copying in 2C02 is done
                        //but (I think) it shouldn't hurt any games if this is done here
                        scanlineSprites.resize(0);
                        int range = 8;
                        if (longSprites)
                        {
                            range = 16;
                        }
                        std::size_t j = 0;
                        for (std::size_t i = spriteDataAddress / 4; i < 64; ++i)
                        {
                            auto diff = (scanline - spriteMemory[i * 4]);
                            if (0 <= diff && diff < range)
                            {
                                if (j >= 8)
                                {
                                    spriteOverflow = true;
                                    break;
                                }
                                scanlineSprites.push_back(i);
                                ++j;
                            }
                        }
                        ++scanline;
                        cycle = 0;
                    }

                    if (scanline >= VisibleScanlines)
                        pipelineState = PPUState::PostRender;
                    break;
                    };
                };
                uint8_t PPU::read(uint16_t addr)
                {
                    return pBus.read(addr);
                }
            }
        }
    }
}