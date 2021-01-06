//
// Created by artyom on 11/21/19.
//

#ifndef GRAPHIC_RENDER_MATRIX_H
#define GRAPHIC_RENDER_MATRIX_H

#include "type/primitive.h"
#include "math/matrix_include.h"

namespace grbus
{
    using Matrix=__Matrix33<real_vt>;

    using Point=__Vector31<real_vt>;

    using Vector=__Vector31<real_vt>;

    using Quaternion=__Quaternion<real_vt>;

}

#endif //GRAPHIC_RENDER_MATRIX_H
