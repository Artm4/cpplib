//
// Created by artyom on 11/21/19.
//

//
// Created by artyom on 11/5/19.
//

#include <iostream>

#include <string.h>
#include <chrono>
#include <render/gi.h>
#include <render/impl/SDL/sdl_imp.h>
#include <render/impl/SDL/sdl_init.h>


namespace grbus {



}


using namespace grbus;

int main() {


    SdlInit sdlInit={640,480};
    SDLImp sdlImp(sdlInit);
    GI gi(&sdlImp);

    gi.init();
    gi.color(0xFF, 0x00, 0x00, 0xFF);
    gi.line(0,0,200,200);

    Point p1{200,200};
    Point p2{300,350};

    gi.line(p1,p2);

    gi.render();

    SDL_Delay( 5000 );

    return 0;
}