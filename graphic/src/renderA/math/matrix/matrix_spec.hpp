//
// Created by artyom on 11/12/19.
//

#ifndef GRAPHIC_MATRIX_SPEC_HPP
#define GRAPHIC_MATRIX_SPEC_HPP

#include <iostream>
#include "matrix.hpp"
#include "operation.hpp"

namespace grbus {

template<typename T>
using __Vector31=__Matrix<T, MatrixDimension<3, 1>, MatrixStoragePolicyFixed>;

template<typename T>
using __Vector13=__Matrix<T, MatrixDimension<1, 3>, MatrixStoragePolicyFixed>;

template<typename T>
using __Vector14=__Matrix<T, MatrixDimension<1, 4>, MatrixStoragePolicyFixed>;

template<typename T>
using __Vector41=__Matrix<T, MatrixDimension<1, 4>, MatrixStoragePolicyFixed>;

template<typename T, size_vt M, size_vt N>
using __MatrixMN=__Matrix<T, MatrixDimension<M, N>, MatrixStoragePolicyFixed>;

template<typename T, size_vt M>
using __MatrixMM=__Matrix<T, MatrixDimension<M, M>, MatrixStoragePolicyFixed>;

template<typename T>
using __Matrix33=__MatrixMM<T, 3>;

template<typename T>
using __Matrix44=__MatrixMM<T, 4>;

template<typename T, size_vt M, size_vt N>
using __MatrixDynMN=__Matrix<T, MatrixDimension<M, N>, MatrixStoragePolicyDynamic>;

template<typename T>
struct __Quaternion: public __Matrix<T, MatrixDimension<1, 4>, MatrixStoragePolicyFixed>
{
    using typeParent=__Matrix<T, MatrixDimension<1, 4>, MatrixStoragePolicyFixed>;
    __Quaternion() = default;

    __Quaternion(MatrixInitType<T, MatrixDimension<1, 4>::order> init)
    : typeParent(init) {}

    __Quaternion(MatrixInitType<T, MatrixDimension<1, 4>::order-1> init)
            : typeParent(init) {}

    __Matrix33<T> getMatrixRotation();

    __Quaternion<T> inv();

    void operator *=(const __Quaternion &multiplier);
};

template<typename T>
__Matrix33<T> __Quaternion<T>::getMatrixRotation()
{
    T x2=(*this)(0)*(*this)(0);
    T y2=(*this)(1)*(*this)(1);
    T z2=(*this)(2)*(*this)(2);

    T xy=(*this)(0)*(*this)(1);
    T xz=(*this)(0)*(*this)(2);
    T yz=(*this)(1)*(*this)(2);

    T wx=(*this)(3)*(*this)(0);
    T wy=(*this)(3)*(*this)(1);
    T wz=(*this)(3)*(*this)(2);

    __Matrix33<T> r{
            {1.0F - 2.0F * (y2 + z2), 2.0F * (xy - wz), 2.0F * (xz + wy)},
            {2.0F * (xy + wz), 1.0F - 2.0F * (x2 + z2), 2.0F * (yz - wx)},
            {2.0F * (xz - wy), 2.0F * (yz + wx), 1.0F - 2.0F * (x2 + y2)}
    };
    return r;
}

template<typename T>
__Quaternion<T> __Quaternion<T>::inv()
{
    __Quaternion<T> inv;
    T squaredM=this->squareMagnitude();

    inv(0)=-1*(*this)(0)/squaredM;
    inv(1)=-1*(*this)(1)/squaredM;
    inv(2)=-1*(*this)(2)/squaredM;
    inv(3)=(*this)(3)/squaredM;
    return inv;
}


template<typename T>
void __Quaternion<T>::operator *=(const __Quaternion<T> &q2)
{
    __Quaternion<T> q1 = *this;
    (*this)(0) = q1(3)*q2(0) + q1(0)*q2(3) + q1(1)*q2(2) - q1(2)*q2(1);

    (*this)(1) = q1(3)*q2(1) - q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0);

    (*this)(2) = q1(3)*q2(2) + q1(0)*q2(1) - q1(1)*q2(0) + q1(2)*q2(3);

    (*this)(3) = q1(3)*q2(3) - q1(0)*q2(0) - q1(1)*q2(1) - q1(2)*q2(2);
}

template<typename T>
__Quaternion<T> operator*(__Quaternion<T> q1,__Quaternion<T> q2)
{
    __Quaternion<T> r;
    r(0) = q1(3)*q2(0) + q1(0)*q2(3) + q1(1)*q2(2) - q1(2)*q2(1);

    r(1) = q1(3)*q2(1) - q1(0)*q2(2) + q1(1)*q2(3) + q1(2)*q2(0);

    r(2) = q1(3)*q2(2) + q1(0)*q2(1) - q1(1)*q2(0) + q1(2)*q2(3);

    r(3) = q1(3)*q2(3) - q1(0)*q2(0) - q1(1)*q2(1) - q1(2)*q2(2);
    return r;
}

/*
 * q=sin(0/2)a+cos(0/2)
 * Represents a rotation through the angle "0" about the unit-length axis "a" that can be applied to a vector "v".
 *
 * q is unit quaternion
 * w=cos(0/2)
 * a - unit vector
 */

template<typename T>
__Vector31<T> transform(__Vector31<T> v,__Quaternion<T> q)
{
    __Vector31<T> b={{q(0),q(1),q(2)}};
    T b2=b(0) * b(0) + b(1) * b(1) + b(2) * b(2);
    return (v * (q(3) * q(3) - b2) + b * (v * b* 2.0F)
                                 + (b%v) * (q(3) * 2.0F));

}

/*
 * result direction Vector4 with forth element 0. (Position vector has value 1 for forth element)
 */
template<typename T>
__Vector41<T> transform(__Vector41<T> v,__Quaternion<T> q)
{
    __Vector41<T> b={{q(0),q(1),q(2), static_cast<T>(1)}};
    T b2=b(0) * b(0) + b(1) * b(1) + b(2) * b(2);
    return (v * (q(3) * q(3) - b2) + b * (v * b* 2.0F)
            + (b%v) * (q(3) * 2.0F));

}

}
#endif //GRAPHIC_MATRIX_SPEC_HPP
