//
// Created by artyom on 11/21/19.
//

#ifndef GRAPHIC_SDL_H
#define GRAPHIC_SDL_H

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <cmath>

#include "render/impl/giimp.h"
#include "type/primitive.h"
#include "sdl_init.h"

namespace grbus {
    class SDLImp : public GIImp {
    public:
        SDLImp(SdlInit init);

        bool init();

        bool color(uint8_vt r, uint8_vt g, uint8_vt b, uint8_vt a);

        bool line(int_vt x1, int_vt y1, int_vt x2, int_vt y2);

        bool line(Point a, Point b);

        bool render();

        bool clearBuffer();

        void point();

        void rect();

        virtual ~SDLImp();

    private:
        //The window we'll be rendering to
        SDL_Window *gWindow = NULL;

//The window renderer
        SDL_Renderer *gRenderer = NULL;

        size_vt width;
        size_vt height;
    };
}

#endif //GRAPHIC_SDL_H
