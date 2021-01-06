//
// Created by artyom on 11/21/19.
//

#include "sdl_imp.h"
namespace grbus {

    SDLImp::SDLImp(SdlInit initSdl) : width{initSdl.width}, height{initSdl.height} {}

    bool SDLImp::init() {
        //Initialization flag
        bool success = true;

        //Initialize SDL
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
            success = false;
        } else {
            //Set texture filtering to linear
            if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
                printf("Warning: Linear texture filtering not enabled!");
            }

            //Create window
            gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                       SDL_WINDOW_SHOWN);
            if (gWindow == NULL) {
                printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
                success = false;
            } else {
                //Create renderer for window
                gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
                if (gRenderer == NULL) {
                    printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
                    success = false;
                } else {
                    //Initialize renderer color
                    SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                    //Initialize PNG loading
                    int imgFlags = IMG_INIT_PNG;
                    if (!(IMG_Init(imgFlags) & imgFlags)) {
                        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
                        success = false;
                    }
                }
            }
        }

        clearBuffer();
        return success;
    }

    bool SDLImp::color(uint8_vt r, uint8_vt g, uint8_vt b, uint8_vt a) {
        return -1 != SDL_SetRenderDrawColor(gRenderer, r, g, b, a);
    }

    void SDLImp::point() {

    }

    bool SDLImp::line(int_vt x1, int_vt y1, int_vt x2, int_vt y2) {
        return -1 != SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
    }

    bool SDLImp::render() {
        SDL_RenderPresent(gRenderer);
        return true;
    }

    bool SDLImp::clearBuffer() {
        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        return -1 != SDL_RenderClear(gRenderer);
    }


    void SDLImp::rect() {

    }

    bool SDLImp::line(Point a, Point b) {
        return line(a(0),a(1),b(0),b(1));
    }

    SDLImp::~SDLImp() {
        SDL_DestroyRenderer( gRenderer );
        SDL_DestroyWindow( gWindow );
        gWindow = NULL;
        gRenderer = NULL;

        //Quit SDL subsystems
        IMG_Quit();
        SDL_Quit();
    }

}

