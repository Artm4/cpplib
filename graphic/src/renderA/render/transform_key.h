//
// Created by artyom on 11/26/19.
//

#ifndef GRAPHIC_TRANSFORM_KEY_H
#define GRAPHIC_TRANSFORM_KEY_H

#include "type/primitive.h"

struct TransformKey
{
    static constexpr uint8_vt NONE=0x0;
    static constexpr uint8_vt UPDATE=0x1;
    static constexpr uint8_vt ROTATE_TRANSLATE=0x2;
};
#endif //GRAPHIC_TRANSFORM_KEY_H
