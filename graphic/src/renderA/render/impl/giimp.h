//
// Created by artyom on 11/21/19.
//

#ifndef GRAPHIC_GIIMP_H
#define GRAPHIC_GIIMP_H


#include "type/primitive.h"
#include "render/render_matrix.hpp"
namespace grbus {
    struct GIImp {
        virtual bool init()=0;

        virtual bool render()=0;

        virtual bool clearBuffer()=0;

        virtual void point()=0;

        virtual bool color(uint8_vt r, uint8_vt g, uint8_vt b, uint8_vt a)=0;

        virtual bool line(int_vt x1, int_vt y1, int_vt x2, int_vt y2)=0;

        virtual bool line(Point a, Point b)=0;

        virtual void rect()=0;
    };

}
#endif //GRAPHIC_GIIMP_H
