//
// Created by artyom on 11/21/19.
//

#ifndef GRAPHIC_GI_H
#define GRAPHIC_GI_H

#include "impl/giimp.h"
#include "render/render_matrix.hpp"

namespace grbus {
    class GI {
    public:
        GI(GIImp *giImpl);

        bool init();

        bool render();

        bool clearBuffer();

        void point();

        bool color(uint8_vt r, uint8_vt g, uint8_vt b, uint8_vt a);

        bool line(int_vt x1, int_vt y1, int_vt x2, int_vt y2);

        bool line(Point a, Point b);

        void rect();

    private:
        GIImp *giImpl;
    };

}
#endif //GRAPHIC_GI_H
