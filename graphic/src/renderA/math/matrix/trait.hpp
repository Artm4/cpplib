//
// Created by artyom on 11/5/19.
//

#ifndef GRAPHIC_TRAIT_HPP
#define GRAPHIC_TRAIT_HPP


#include <type_traits>

namespace grbus{

template<typename Matrix>
struct IsMatrix {
    template<typename MD, typename=std::enable_if<(MD::TypeDimension::size > 0 && MD::TypeDimension::order > 0)>>
    static std::true_type test(void *);

    static std::false_type test(...);

    using Type=decltype(test<Matrix>(nullptr));
};


template<typename MatrixDimension>
struct IsMatrixDimension {
    template<typename MD, typename=std::enable_if<(MD::size > 0 && MD::order > 0)>>
    static std::true_type test(void *);

    static std::false_type test(...);

    using Type=decltype(test<MatrixDimension>(nullptr));
};

}

#endif //GRAPHIC_TRAIT_HPP
