#ifndef PPU_STATE_H
#define PPU_STATE_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Ppu{
                enum class PPUState{
                    PreRender,
                    Render,
                    PostRender,
                    VerticalBlank
                };
            }
        }
    }
}
#endif