//
// Created by artyom on 11/25/19.
//

#ifndef GRAPHIC_CONSTANT_H
#define GRAPHIC_CONSTANT_H

#include <cmath>
#include "primitive.h"
namespace grbus
{
    namespace constant {
        constexpr real_vt pi = std::acos(-1);
        constexpr real_vt radianPerDegree = 2*pi/360;
    }

}
#endif //GRAPHIC_CONSTANT_H
