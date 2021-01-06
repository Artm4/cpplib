//
// Created by artyom on 11/5/19.
//

#ifndef GRAPHIC_MATRIX_HPP
#define GRAPHIC_MATRIX_HPP

#ifndef DETERM_DEBUG
//#define DETERM_DEBUG
#endif

#include <vector>
#include <cassert>
#include <numeric>
#include <algorithm>

#include "type/primitive.h"
#include "type/traits.hpp"
#include "math/arithmetic.hpp"
#include "util/memory.hpp"

#include "storage.hpp"
#include "trait.hpp"
//#include "operation.hpp"

//Opt1: Could be type,dim and init the sizes, fixed data
//Opt2: Could be type,size , same size for dimension, vector data
//Opt3: Combine 1 and 2 with specialization
//template <typename T>
//class Matrix
//{
//
//};
namespace grbus_operation_trait{
    template<typename T,typename ListColsCurrent,
            typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
    struct MatrixAdjSum;


template<typename T,typename ListColsCurrent,
        typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
struct MatrixAdj;
    

template <typename Storage,size_vt Row,size_vt Col>
struct AdjRowCol;

template<typename Storage,uint_vt N>
struct Cofactor;

}

namespace grbus {




template<typename T>
void print(T *a, int size) {
    for (int i = 0; i < size; i++) {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

template<typename T, size_vt N>
struct MatrixInit {
    using type=std::initializer_list<typename MatrixInit<T, N - 1>::type>;
};

template<typename T>
struct MatrixInit<T, 1> {
    using type=std::initializer_list<T>;
};

template<typename T, size_vt N>
using MatrixInitType=typename MatrixInit<T, N>::type;

template<size_vt... Dimensions>
struct MatrixDimension {
    using typeSlicedRowDimension=typename grbus::RemoveFirstPackArg<MatrixDimension, Dimensions...>::type;
    using typeSlicedColDimension=typename grbus::RemoveSecondPackArg<MatrixDimension, Dimensions...>::type;
    using typeTran=MatrixDimension<Dimensions...>;

    static constexpr size_vt size = grbus::multiply<Dimensions...>();
    static constexpr size_vt order = sizeof...(Dimensions);

    const size_vt getSize() { return size; }

    const size_vt getOrder() { return order; }

    MatrixDimension() : extents{Dimensions...} {}

    size_vt getExtentSize(size_vt index) { return extents[index]; }

    size_vt *getExtents() { return extents; }

private:
    size_vt extents[order]; // size for each dimension , 2x3, 3x1
};


template<size_vt FirstDimension, size_vt SecondDimension>
struct MatrixDimension<FirstDimension, SecondDimension> {
    using typeSlicedRowDimension=MatrixDimension<1,SecondDimension>;
    using typeSlicedColDimension=MatrixDimension<FirstDimension,1>;
    using typeTran=MatrixDimension<SecondDimension,FirstDimension>;

    static constexpr size_vt size = FirstDimension * SecondDimension;
    static constexpr size_vt order = 2;

    static constexpr size_vt firstDim = FirstDimension;
    static constexpr size_vt secondDim = SecondDimension;

    const size_vt getSize() { return size; }

    const size_vt getOrder() { return order; }

    MatrixDimension() : extents{FirstDimension, SecondDimension} {}

    size_vt getExtentSize(size_vt index) {
        //"getExtentSize(): Out of bound index."
        if (0 == index) {
            return FirstDimension;
        } else {
            return SecondDimension;
        }

    }

    size_vt *getExtents() { return extents; }

private:
    size_vt extents[order]; // size for each dimension , 2x3, 3x1
};

template<size_vt FirstDimension>
struct MatrixDimension<FirstDimension> {
    using typeSlicedRowDimension=MatrixDimension<0>;
    using typeSlicedColDimension=MatrixDimension<0>;
    using typeTran=MatrixDimension<FirstDimension>;

    static constexpr size_vt size = FirstDimension;
    static constexpr size_vt order = 1;

    const size_vt getSize() { return size; }

    const size_vt getOrder() { return order; }

    MatrixDimension() : extents{FirstDimension} {}

    size_vt getExtentSize(size_vt index) {
        //"getExtentSize(): Out of bound index."
        assert(index < order);
        return FirstDimension;
    }

    size_vt *getExtents() { return extents; }

private:
    size_vt extents[order]; // size for each dimension , 2x3, 3x1
};

template<typename MatrixDimension>
struct MatrixSlice;

template<typename MatrixDimensionT>
struct PickStride;

template<uint_vt N>
struct PickStride<MatrixDimension<1,N>>
{
    static constexpr size_vt pick(MatrixSlice<MatrixDimension<1,N>> const &ms)
    {
        return ms.getStride(1);
    }
};

template<uint_vt N>
struct PickStride<MatrixDimension<N,1>>
{
    static constexpr size_vt pick(MatrixSlice<MatrixDimension<N,1>> const &ms)
    {
        return ms.getStride(0);
    }
};

template<typename MatrixDimensionT,typename MatrixDimensionB,size_vt D>
struct CopyStride
{
    static constexpr void copy(const size_vt*  bStrides,size_vt*  strides)
    {
        static_assert(
                MatrixDimensionT::order < MatrixDimensionB::order,
                "Matrix order should be less or equal than bounding matrix order");
        // Copy strides without D position :
        // * copy D elements to D - 1  th position to new strides
        // * copy left elements (New total - D) to returned pointer from D+1 position
        std::copy_n(bStrides + D + 1, MatrixDimensionT::order - D, std::copy_n(bStrides, D, strides));
    }
};

template<typename MatrixDimensionB,uint_vt N,size_vt D>
struct CopyStride<MatrixDimension<1,N>,MatrixDimensionB,D>
{
    static constexpr void copy(const size_vt*  bStrides,size_vt*   strides)
    {
        static_assert(
                MatrixDimension<1,N>::order == MatrixDimensionB::order,
                "Matrix order should be equal to bounding matrix order");
        std::copy_n(bStrides, MatrixDimension<1,N>::order, strides);
    }
};

template<typename MatrixDimensionB,uint_vt N,size_vt D>
struct CopyStride<MatrixDimension<N,1>,MatrixDimensionB,D>
{
    static constexpr void copy(const size_vt*  bStrides,size_vt*  strides)
    {
        static_assert(
                MatrixDimension<N,1>::order == MatrixDimensionB::order,
                "Matrix order should be equal to bounding matrix order");
        std::copy_n(bStrides, MatrixDimension<N,1>::order, strides);
    }
};

template<typename MatrixDimension>
struct MatrixSlice {
    using TypeDimenstion=MatrixDimension;
    static constexpr size_vt order = MatrixDimension::order;

    MatrixSlice() : start{0} {
        init();
    }

    template<typename MatrixDim, size_vt D>
    MatrixSlice(const MatrixSlice<MatrixDim> &boundingSlice, grbus::size_constant<D>, size_vt n);

    void init();

    size_vt *getStrides() const { return strides; }

    size_vt *getStrides() { return strides; }

    size_vt getStride(size_vt index) const {
        //"getStride(): Out of bound index."
        assert(index < MatrixDimension::order);
        return strides[index];
    }

    size_vt getFirstStride() const { return strides[0]; }

    size_vt getFirstStride() { return strides[0]; }

    MatrixDimension getDimension() { return dimension; }

    size_vt getStart() const { return start; }

    size_vt getStart() { return start; }

    MatrixSlice<typename MatrixDimension::typeSlicedRowDimension> reduceSliceRow(size_vt row);

    MatrixSlice<typename TypeDimenstion::typeSlicedColDimension> reduceSliceCol(size_vt col);

    template<typename M>
    size_vt operator()(M x);

    template<typename M>
    size_vt operator()(M x) const;

    template<typename M>
    size_vt operator()(M x, M y);

    template<typename M>
    size_vt operator()(M x, M y) const;

    template<typename... Args>
    size_vt operator()(Args... args);

    template<typename... Args>
    size_vt operator()(Args... args) const;

    template<typename R>
    size_vt offset(R &&);

    size_vt strides[order]; // offset for each index, because elements are stored in memory as sequence not matrix

private:
    MatrixDimension dimension;
    size_vt start;


};

template<typename MatrixDimension>
MatrixSlice<typename MatrixDimension::typeSlicedRowDimension>
MatrixSlice<MatrixDimension>::reduceSliceRow(size_vt row) {
    return MatrixSlice<typename MatrixDimension::typeSlicedRowDimension>(*this, grbus::size_constant<0>(), row);
}

template<typename MatrixDimension>
MatrixSlice<typename MatrixDimension::typeSlicedColDimension>
MatrixSlice<MatrixDimension>::reduceSliceCol(size_vt col) {
    return MatrixSlice<typename MatrixDimension::typeSlicedColDimension>(*this, grbus::size_constant<1>(), col);
}

template<typename MatrixDimension>
template<typename M>
inline size_vt MatrixSlice<MatrixDimension>::operator()(M x){
    static_assert(2 == MatrixDimension::order
                  && (1 == MatrixDimension::firstDim || 1==  MatrixDimension::secondDim)
            , "Matrix dimension should be 1xN or Nx1");
    return start+PickStride<MatrixDimension>::pick(*this) * x;
}

template<typename MatrixDimension>
template<typename M>
inline size_vt MatrixSlice<MatrixDimension>::operator()(M x) const{
    static_assert(2 == MatrixDimension::order
                  && (1 == MatrixDimension::firstDim || 1==  MatrixDimension::secondDim)
            , "Matrix dimension should be 1xN or Nx1");
    return start+PickStride<MatrixDimension>::pick(*this) * x;
}

template<typename MatrixDimension>
template<typename M>
inline size_vt MatrixSlice<MatrixDimension>::operator()(M x, M y){
    static_assert(2 == MatrixDimension::order, "Arguments size different from Matrix order");
    return start+getStride(0) * x + getStride(1) * y;
}

template<typename MatrixDimension>
template<typename M>
inline size_vt MatrixSlice<MatrixDimension>::operator()(M x, M y) const{
    static_assert(2 == MatrixDimension::order, "Arguments size different from Matrix order");
    return start+getStride(0) * x + getStride(1) * y;
}

template<typename MatrixDimension>
template<typename... Args>
inline size_vt MatrixSlice<MatrixDimension>::operator()(Args... args) {
    static_assert(sizeof...(Args) == MatrixDimension::order, "Arguments size different from Matrix order");
    size_vt range[order] = {size_vt(args)...};
    return offset(range);
}

template<typename MatrixDimension>
template<typename... Args>
inline size_vt MatrixSlice<MatrixDimension>::operator()(Args... args) const {
    static_assert(sizeof...(Args) == MatrixDimension::order, "Arguments size different from Matrix order");
    size_vt range[order] = {size_vt(args)...};
    return offset(range);
}


template<typename MatrixDimension>
template<typename R>
inline size_vt MatrixSlice<MatrixDimension>::offset(R &&range) {
    using std::begin;
    constexpr size_vt zero = 0;
    return start+std::inner_product(strides, strides + order, begin(range), zero);
}


template<typename MatrixDimension>
template<typename MatrixDimensionBound, size_vt D>
MatrixSlice<MatrixDimension>::MatrixSlice(const MatrixSlice<MatrixDimensionBound> &boundingSlice,
                                          grbus::size_constant<D>, size_vt n)
        : start(boundingSlice.getStart() + n * boundingSlice.getStride(D)) {

    CopyStride<MatrixDimension,MatrixDimensionBound,D>::copy(boundingSlice.strides,strides);

}

template<typename MatrixDimension>
void inline MatrixSlice<MatrixDimension>::init() {
    strides[MatrixDimension::order - 1] = 1;
    for (size_vt i = MatrixDimension::order - 1; i != 0; i--) {
        strides[i - 1] = strides[i] * dimension.getExtentSize(i);
    }
}



template<typename T, typename Node>
struct NodeGeneric;

template<typename T,
        typename MatrixDimension,
        template<typename, size_vt> class MatrixStoragePolicy,
        typename=std::enable_if<(IsMatrixDimension<MatrixDimension>::Type::value)>
>
struct __Matrix;

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
struct __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> {
public:
    using TypeDimension=MatrixDimensionT;
    using TypeMatrixStoragePolicy=MatrixStoragePolicy<T, MatrixDimensionT::size>;
    using Type=T;
    using TypeMatrix=__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>;

    MatrixStoragePolicy<T, MatrixDimensionT::size> storage;

    static constexpr size_vt getSize() { return MatrixDimensionT::size; }

    static constexpr size_vt size = MatrixDimensionT::size;

    __Matrix() = default;

    __Matrix(T *a);

    __Matrix(MatrixInitType<T, MatrixDimensionT::order>);
    __Matrix(MatrixInitType<T, MatrixDimensionT::order-1>);

    template <typename Slice,typename Storage>
    __Matrix(Slice slice,Storage storage):slice{slice},storage(storage)
    {}

    template <typename Storage>
    __Matrix(Storage storage):storage(storage)
    {}

    template<typename NodeB>
    __Matrix(NodeGeneric<T,NodeB> const& node)
    {
        auto result = node.getNode().result();
        this->storage = result;
    }


    inline T& get(size_vt index) {return storage[index];}
    inline const T get(size_vt index) const {return storage[index];}

    template<typename V>
    inline T& el(V row,V col) {return (*this)(row,col);}

    template<typename V>
    inline T& el(V col) {return (*this)(col);}

    void put(size_vt index, T v) {storage.put(index, v);}

    __Matrix<T,typename MatrixDimensionT::typeSlicedRowDimension,MatrixStoragePolicyRef> row(size_vt row);
    __Matrix<T,typename MatrixDimensionT::typeSlicedColDimension,MatrixStoragePolicyRef> col(size_vt col);


    T *data() { return storage.data(); }

    const T *data() const { return storage.data(); }

    template<typename M>
    T &operator()(M x, M y);

    template<typename M>
    T operator() (M x, M y) const;

    template<typename... Args>
    T &operator()(Args... args);

    template<typename... Args>
    T operator()(Args... args) const;

    template<typename Node>
    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator=
            (const NodeGeneric<T, Node> node);

    const TypeMatrixStoragePolicy result() const { return storage; }

    template<typename Node>
    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator+=
            (const NodeGeneric<T, Node> node);

    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator+=
            (T scalar);

    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator+=
            (__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> const& m);

    template<typename Node>
    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator*=
            (const NodeGeneric<T, Node> node);

    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator*=
            (T scalar);

    __Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &operator*=
            (__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> const& m);


    __Matrix<T,  typename MatrixDimensionT::typeTran, MatrixStoragePolicy> inv();

    __Matrix<T, typename MatrixDimensionT::typeTran, MatrixStoragePolicy> tran();


    T det()
    {
        return detDownUp();
    }

    T detDownUp()
    {
        static_assert(MatrixDimensionT::order==2);
        static_assert(MatrixDimensionT::firstDim==MatrixDimensionT::secondDim);
        using ListN=CTTypelistN<size_vt ,MatrixDimensionT::firstDim>;
        return grbus_operation_trait::MatrixAdjSum
               <T,ListN,ListN,ListN,Reverse<ListN>,__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>>::result(*this);
    }

    T detUpDown()
    {
        static_assert(MatrixDimensionT::order==2);
        static_assert(MatrixDimensionT::firstDim==MatrixDimensionT::secondDim);
        using ListN=CTTypelistN<size_vt ,MatrixDimensionT::firstDim>;
        return grbus_operation_trait::MatrixAdjSum
               <T,ListN,ListN,ListN,ListN,__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>>::result(*this);
    }

    template <size_vt Row,size_vt Col>
    T adj()
    {
        return grbus_operation_trait::AdjRowCol<TypeMatrix,Row,Col>::result(*this);
    }

    T magnitude();
    T squareMagnitude();

    void normalize();

private:
    MatrixSlice<MatrixDimensionT> slice;
};

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
T __Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::magnitude()
{
    return sqrt(std::inner_product(this->data(),this->data()+this->getSize(),this->data(), static_cast<T>(0)));
}

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
T __Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::squareMagnitude()
{
    return std::inner_product(this->data(),this->data()+this->getSize(),this->data(),static_cast<T>(0));
}


template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
void __Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::normalize()
{
    T magnitude=this->magnitude();
    T* data=this->data();

    T d=1.0/(magnitude);
    for(size_vt i=0;i<this->getSize();i++)
    {
        data[i]=data[i]*d;
    }
}



template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T,typename MatrixDimensionT::typeTran, MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::tran()
{
    MatrixStoragePolicy<T,MatrixDimensionT::typeTran::size> r;

    constexpr size_vt rowsN=MatrixDimensionT::firstDim;
    constexpr size_vt colsN=MatrixDimensionT::secondDim;

    static_assert(MatrixDimensionT::order==2);

    for(size_vt i=0;i<rowsN*colsN;i++)
    {
        size_vt row=i/rowsN;
        size_vt col=i%colsN;
        r[i]=(*this)(col,row);
    }

    return r;
}


template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, typename MatrixDimensionT::typeTran, MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::inv()
{
    using TypeCofactor=__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>;
    TypeCofactor cofactor;
    grbus_operation_trait::Cofactor<TypeCofactor,TypeCofactor::size>::result(*this,cofactor);
    return (1/this->det())*(cofactor.tran());
}

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename Node>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator=
        (const NodeGeneric<T, Node> node) {
    // should eval to get result
    auto result = node.getNode().result();
    this->storage = result;
    return *this;
}


//Matrix+=Generic
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename Node>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator+=
        (const NodeGeneric<T, Node> node) {
    for(int i=0;i<getSize();i++)
    {
        this->get(i) += node.get(i);
    }
    return *this;
}

//Matrix+=Matrix
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator+=
        (__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> const& m)
{
    for(int i=0;i<getSize();i++)
    {
        this->get(i) += m.get(i);
    }
    return *this;
}

//Matrix+=Scalar
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator+=
        (T scalar) {
    for(int i=0;i<getSize();i++)
    {
        this->get(i) += scalar;
    }
    return *this;
}


//Matrix*=Generic
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename Node>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator*=
        (const NodeGeneric<T, Node> node) {

    *this=node*(*this);
    return *this;
}

//Matrix*=Scalar
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator*=
        (T scalar) {
    for(int i=0;i<getSize();i++)
    {
        this->get(i) *= scalar;
    }
    return *this;
}

//Matrix*=Matrix
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator*=
    (__Matrix<T, MatrixDimensionT, MatrixStoragePolicy> const& m)
{
    *this=matrixMult((*this),m);
    return *this;
}

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::__Matrix(MatrixInitType<T, MatrixDimensionT::order> init) {
    // this will not work for dynamic storage should make init/reserve method for storages
    grbus::insert_flattened(init, storage.data());
}

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::__Matrix(MatrixInitType<T, MatrixDimensionT::order-1> init) {
    // this will not work for dynamic storage should make init/reserve method for storages
    grbus::insert_flattened(init, storage.data());
}

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::__Matrix(T *a) {}


template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename M>
inline T &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator()(M x, M y) {
    return *(data() + slice(x, y));
};

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename M>
inline  T __Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator()(M x, M y) const {
    return *(data() + slice(x, y));
};


template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename... Args>
inline T &__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator()(Args... args) {
    return *(data() + slice(args...));
};

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
template<typename... Args>
inline T __Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::operator()(Args... args) const{
    return *(data() + slice(args...));
};

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T,typename MatrixDimensionT::typeSlicedRowDimension,MatrixStoragePolicyRef>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::row(size_vt row)
{
    auto sliced=slice.reduceSliceRow(row);
    MatrixStoragePolicyRef<T,MatrixDimensionT::typeSlicedRowDimension::size> storageRef;
    storageRef.a=storage.data();
    return {sliced,storageRef};
};

template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T,typename MatrixDimensionT::typeSlicedColDimension,MatrixStoragePolicyRef>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::col(size_vt col)
{
    auto sliced=slice.reduceSliceCol(col);
    MatrixStoragePolicyRef<T,MatrixDimensionT::typeSlicedColDimension::size> storageRef;
    storageRef.a=storage.data();
    return {sliced,storageRef};
};




/*
 *
	1 2 3 4 5 6 7 8 9

	1 2 3	    3,1
	4 5 6    6- 1*3+2*1
	7 8 9

	1 4 7       1,3
	2 5 8	 8- 1*1+2*3
	3 6 9

	1 2 3 4 5 6

	1 2 3	   3,1
	4 5 6   5- 1*3+1*1

	1 4
	2 5        1,3 reverse origin strides use same storage, instead 2,1 with transpose storage
	3 6     6- 1*1+2*2
                3- 1*2+0*3

    BECAUSE:
	x,y x*rSize+y*colSize , in storageA
	y,x transpose - y*colSize+x*rSize , in same storageA, but strides should be orig reversed
 */

/*
 * // Do not work for Sum/Mult Expressions, because storage is manipulated
 * Tested for col and row reduction.
 * Could be implemented as element by element transpose (storage reorder)
 *
 *
 *
template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T,typename MatrixDimensionT::typeTran, MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::tran()
{
    MatrixSlice<typename MatrixDimensionT::typeTran> slice;
    std::copy_n(this->slice.getStrides(),slice.order,slice.getStrides());
    std::reverse(slice.getStrides(),slice.getStrides()+slice.order);
    return {slice,storage};
}
 */

    /*
     * Could optimize by one loop and filling storage with calc row and col
     * from i<=rowsN*colsN, row=i/rowsN, col=i%colsN
     *
     template<typename T,
        typename MatrixDimensionT, template<typename, size_vt> class MatrixStoragePolicy>
__Matrix<T,typename MatrixDimensionT::typeTran, MatrixStoragePolicy>
__Matrix<T, MatrixDimensionT, MatrixStoragePolicy>::tran()
{
    __Matrix<T,typename MatrixDimensionT::typeTran, MatrixStoragePolicy> r;

    constexpr size_vt rowsN=MatrixDimensionT::firstDim;
    constexpr size_vt colsN=MatrixDimensionT::secondDim;

    static_assert(MatrixDimensionT::order==2);

    for(size_vt i=0;i<rowsN;i++)
        for(size_vt j=0;j<colsN;j++)
            r(j,i)=(*this)(i,j);
    return r;
}
     */

}

#endif //GRAPHIC_MATRIX_HPP
