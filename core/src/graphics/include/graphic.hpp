#ifndef GRAPHIC_H
#define GRAPHIC_H

#include <SDL2/SDL.h>
#include "../../../libs/gl3w/gl3w.h"

namespace Gemunin{
    namespace Core{
        namespace Graphics{
            class Graphic{
                public:
                    Graphic();
                   SDL_Window* getWindow();
                   SDL_GLContext getGLContext();
                   ~Graphic();
                private:
                    SDL_Window* window;
                    SDL_GLContext gl_context;

            };
        }
    }
}
#endif