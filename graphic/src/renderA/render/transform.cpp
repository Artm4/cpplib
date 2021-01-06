//
// Created by artyom on 11/25/19.
//

#include "transform.h"
namespace grbus
{

void Transform::rotateRad(Vector base, real_vt rad) {
    Quaternion q{sin(rad/2)*base(0),sin(rad/2)*base(1),sin(rad/2)*base(2),cos(rad/2)};
    rotation*=q;
    update=TransformKey::UPDATE;
    transformType=TransformKey::ROTATE_TRANSLATE;
}

void Transform::rotateDeg(Vector base, real_vt deg) {
    rotateRad(base,degToRad(deg));
}

void Transform::translate(Vector v) {
    translation+=v;
    update=TransformKey::UPDATE;
    transformType=TransformKey::ROTATE_TRANSLATE;
}

Vector Transform::apply(Vector target)
{
    // Update could be mask
    if(update&TransformKey::UPDATE)
    {
        transfMatrix = rotation.getMatrixRotation();
    }
    update=TransformKey::NONE;

    // If only rotate or translate do not use
    // rotation matrix but quaternion
    if(!(transformType^TransformKey::ROTATE_TRANSLATE))
    {
        return applyRotTran(target);
    }

    return transfMatrix*target+translation;
}

Vector Transform::applyRotTran(Vector target) {
    return transform(target,rotation)+translation;
}

Transform Transform::createInverse()
{
    if(update&TransformKey::UPDATE)
    {
        transfMatrix = rotation.getMatrixRotation();
    }
    Transform trInv;
    real_vt invS=-1;
    trInv.translation=invS*translation;
    trInv.rotation=rotation.inv();
    trInv.transfMatrix=transfMatrix.tran();
    return trInv;
}

}