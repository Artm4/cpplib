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


namespace grbus {



}


using namespace grbus;

int main() {


    SdlInit sdlInit={640,480};
    SDLImp sdlImp(sdlInit);
    GI gi(&sdlImp);

    gi.init();

    //Main loop flag
    bool quit = false;

    //Event handler
    SDL_Event e;

    Vector move{1,1,0};
    Point obj{10,10,0};
    Point objElA{13,14,0};
    Point objElPos;

    Matrix transform{
            {0.15425144988,-0.98803162409,0},
            {0.98803162409,0.15425144988,0},
            {0,0,0}
    };

    //While application is running
    while( !quit )
    {
        //Handle events on queue
        while( SDL_PollEvent( &e ) != 0 )
        {
            //User requests quit
            if( e.type == SDL_QUIT )
            {
                quit = true;
            }
        }

        gi.clearBuffer();
        gi.color(0xFF, 0x00, 0x00, 0xFF);

        obj+=move;


        objElA=objElA*transform;

        objElPos=obj+objElA;

        gi.line(obj,objElPos);

        gi.render();

    }

    return 0;
}