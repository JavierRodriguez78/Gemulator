#ifndef NAME_TABLE_MIRRORING_H
#define NAME_TABLE_MIRRORING_H
namespace Gemunin{
    namespace Nintendo{
        namespace Nes{
            namespace Mappers{
                enum class NameTableMirroring{
                    Horizontal  = 0,
                    Vertical    = 1,
                    FourScreen  = 8,
                    OneScreenLower,
                    OneScreenHigher,
                };
            }
        }
    }
}
#endif