//
// Created by artyom on 11/25/19.
//

#ifndef GRAPHIC_TRANSFORM_H
#define GRAPHIC_TRANSFORM_H

#include "render_matrix.hpp"
#include "transform_key.h"

namespace grbus
{
class Transform
{
public:
    void rotateRad(Vector base,real_vt rad);
    void rotateDeg(Vector base,real_vt deg);
    void translate(Vector v);
    Vector apply(Vector target);
    Transform createInverse();

private:
    Vector applyRotTran(Vector target);

    /**
     * Identity quaternion
     */
    Quaternion rotation{0,0,0,1};

    Vector translation{0,0,0,0};
    /**
     * Translation not included in Matrix 3x3
     */
    Matrix transfMatrix{
            {1,0,0},
            {0,1,0},
            {0,0,1}
    };

    uint8_vt update=TransformKey::NONE;
    uint8_vt transformType=TransformKey::NONE;
};
}


#endif //GRAPHIC_TRANSFORM_H
