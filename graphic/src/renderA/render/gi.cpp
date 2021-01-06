//
// Created by artyom on 11/21/19.
//

#include "gi.h"
namespace grbus {
    GI::GI(GIImp *giImpl) : giImpl(giImpl) {}

    bool GI::init() { return giImpl->init(); }

    bool GI::render() { return giImpl->render(); }

    bool GI::clearBuffer() { return giImpl->clearBuffer(); }

    bool GI::color(uint8_vt r, uint8_vt g, uint8_vt b, uint8_vt a) {
        return giImpl->color(r, g, b, a);
    }

    bool GI::line(int_vt x1, int_vt y1, int_vt x2, int_vt y2) {
        return giImpl->line(x1, y1, x2, y2);
    }

    bool GI::line(Point a, Point b) {
        return giImpl->line(a,b);
    }
}


