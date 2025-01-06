#ifndef MAPPER_TYPE_H
#define MAPPER_TYPE_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                enum class MapperType{
                    NROM  = 0,
                    SxROM = 1,
                    UxROM = 2,
                    CNROM = 3,
                    MMC3  = 4,
                    AxROM = 7,
                    ColorDreams = 11,
                    GxROM = 66,
                };
            }

        }
    }
}
#endif