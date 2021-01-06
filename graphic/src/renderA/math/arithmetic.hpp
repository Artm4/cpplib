//
// Created by artyom on 9/25/19.
//

#ifndef GRAPHIC_ARITHMETIC_HPP
#define GRAPHIC_ARITHMETIC_HPP

#include <cmath>
#include "type/constant.h"

namespace grbus
{

template <uint_vt First,uint_vt... Dimensions>
struct Multiply
{
    static constexpr uint_vt value=First*Multiply<Dimensions...>::value;
};

template <uint_vt First>
struct Multiply<First>
{
    static constexpr uint_vt value=First;
};

template <typename T,T base,uint_vt E>
struct Pow
{
    static constexpr T value=base*Pow<T,base,E-1>::value;
};

template <typename T,T base>
struct Pow<T,base,1>
{
    static constexpr T value=base;
};

template <typename T,T base>
struct Pow<T,base,0>
{
    static constexpr T value=1;
};


template <uint_vt First>
constexpr uint_vt multiply()
{
    return First;
};


template <uint_vt First,uint_vt Second,uint_vt... Dimensions>
constexpr uint_vt multiply()
{
    return First*multiply<Second,Dimensions...>();
};

template<typename T>
inline T sqrt(T x)
{
    return std::sqrt(x);
}

inline real_vt degToRad(real_vt deg)
{
    return deg*grbus::constant::radianPerDegree;
}

}
#endif //GRAPHIC_ARITHMETIC_HPP
