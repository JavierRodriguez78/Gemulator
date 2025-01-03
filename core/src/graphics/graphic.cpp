#include "include/graphic.hpp"

namespace Gemunin{
    namespace Core{
        namespace Graphics{
            Graphic::Graphic(){
                // Inicializar SDL
                if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
                    printf("Error: %s\n", SDL_GetError());
                    return ;
                }
                window= SDL_CreateWindow("Gemunin", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
                SDL_MaximizeWindow(window);
                gl_context = SDL_GL_CreateContext(window);
                SDL_GL_MakeCurrent(window, gl_context);
                SDL_GL_SetSwapInterval(1); // Enable vsync
                // Inicializar gl3w
                if (gl3wInit()) {
                    printf("Failed to initialize OpenGL loader!\n");
                return ;
                }
            };
            
            SDL_Window* Graphic::getWindow()
            {
                return window;
            };

             SDL_GLContext Graphic::getGLContext()
             {
                return gl_context;
             };

             Graphic::~Graphic(){
                SDL_GL_DeleteContext(gl_context);
                SDL_DestroyWindow(window);
                SDL_Quit();
             }
        }
    }
}