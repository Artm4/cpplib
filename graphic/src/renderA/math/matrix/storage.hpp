//
// Created by artyom on 11/5/19.
//

#ifndef GRAPHIC_STORAGE_HPP
#define GRAPHIC_STORAGE_HPP

#include <vector>
#include <cassert>
#include <numeric>

#include "type/primitive.h"
#include "type/traits.hpp"
#include "math/arithmetic.hpp"
#include "util/memory.hpp"

namespace grbus {

template<typename T, size_vt size>
struct MatrixStoragePolicyFixed {
    using Type=T;

    T a[size] = {};

    static constexpr size_vt getSize() {
        return size;
    }

    T get(size_vt index) {
        return a[index];
    }

    void put(size_vt index, T v) {
        a[index] = v;
    }

    T &operator[](size_vt index) {
        return a[index];
    }

    T const& operator[](size_vt index) const {
        return a[index];
    }

    T *data() {
        return a;
    }

    T const *data() const {
        return a;
    }
};


template<typename T, size_vt size>
struct MatrixStoragePolicyDynamic {
    using Type=T;

    std::vector<T> a;

    MatrixStoragePolicyDynamic() : a{size} {}

    static constexpr size_vt getSize() {
        return size;
    }

    T get(size_vt index) {
        return a[index];
    }

    void put(size_vt index, T v) {
        a[index] = v;
    }

    T &operator[](size_vt index) {
        return a[index];
    }

    T const &operator[](size_vt index) const {
        return a[index];
    }

    T *data() {
        return a.data();
    }

    T const *data() const {
        return a.data();
    }
};

template<typename T, size_vt size>
struct MatrixStoragePolicyRef {
    using Type=T;

    T *a;

    static constexpr size_vt getSize() {
        return size;
    }

    T get(size_vt index) {
        return a[index];
    }

    void put(size_vt index, T v) {
        a[index] = v;
    }

    T &operator[](size_vt index) {
        return a[index];
    }

    T const &operator[](size_vt index) const {
        return a[index];
    }

    T *data() {
        return a;
    }

    T const *data() const {
        return a;
    }
};

}
#endif //GRAPHIC_STORAGE_HPP
