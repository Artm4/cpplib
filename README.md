# cpplib
Various cpp libs:
* Algorithms implementations

   Sorting algorithms: slow and fast comparison sorts, linear time sorting.

* Math library for graphic.

   Implements Vector and Matrix operations. Most Matrix operations support n-dimensional matrix.

   Interesting part is Matrix determinant calculation based ot template expression evaluation.
   It is used in matrix invert operation.

   Implementation inspired by Stroustrup work.

##Example of Math lib usage
```

#include <iostream>

#include <string.h>
#include <chrono>
#include "render/render_include.h"


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

    Point o1{1,1,0};
    Point o2{20,1,0};
    Point o3{20,20,0};
    Point o4{1,20,0};

    Point vb1{0,0,1};

    Transform t1;
    t1.rotateDeg(vb1,1);
    t1.translate({1,1,0});

    Transform t1i=t1.createInverse();

    Transform t2;
    t2.translate({200,200,0});

    Vector vTr=t1.apply(o1);
    Vector vInv=t1i.apply(vTr);


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

        o1=t1.apply(o1);
        o2=t1.apply(o2);
        o3=t1.apply(o3);
        o4=t1.apply(o4);

        Vector wo1=t2.apply(o1);
        Vector wo2=t2.apply(o2);
        Vector wo3=t2.apply(o3);
        Vector wo4=t2.apply(o4);

        gi.line(wo1,wo2);
        gi.line(wo2,wo3);
        gi.line(wo3,wo4);
        gi.line(wo4,wo1);

        gi.render();

    }

    return 0;
}
```