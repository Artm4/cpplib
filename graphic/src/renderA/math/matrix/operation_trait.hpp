//
// Created by artyom on 11/5/19.
//

#ifndef GRAPHIC_MATRIX_TRAIT_HPP
#define GRAPHIC_MATRIX_TRAIT_HPP
#include "type/traits.hpp"

namespace grbus{
template<typename T, typename Node>
struct NodeGeneric;

template<typename N>
struct NodeScalar;

template<typename T, typename NodeA, typename NodeB>
struct NodeAdd;

template<typename T, typename NodeA, typename NodeB>
struct NodeMult;

};

namespace grbus_operation_trait
{

using namespace grbus;

template <typename MatrixDimensionA,typename MatrixDimensionB,
        typename Enable=void>
struct MultDimensionTrait;


template<typename MatrixDimensionA,typename MatrixDimensionB>
struct MultDimensionTrait<MatrixDimensionA,MatrixDimensionB,
        typename std::enable_if<MatrixDimensionA::order==MatrixDimensionB::order &&
                                MatrixDimensionA::order==2>::type >
{
    static constexpr int a=1;
};

struct MultDimensionTraitResultObject
{
    template <size_vt MM ,size_vt NN, size_vt VV>
    static MatrixDimension<MM,VV> multResult(MatrixDimension<MM,NN> a,MatrixDimension<NN,VV> b)
    {
        MatrixDimension<MM,VV> r;
        return r;
    }

};

template <typename MatrixDimensionA,typename MatrixDimensionB>
struct MultDimensionTraitResult
{
    using Type=MatrixDimensionA;
};

template <size_vt M ,size_vt N, size_vt V>
struct MultDimensionTraitResult<grbus::MatrixDimension<M,N>,grbus::MatrixDimension<N,V>>
{
using Type=MatrixDimension<M,V>;
};

template <typename MatrixDimensionA,typename MatrixDimensionB>
struct SumDimensionTraitResult
{

};

template <size_vt M ,size_vt N>
struct SumDimensionTraitResult<grbus::MatrixDimension<M,N>,grbus::MatrixDimension<M,N>>
{
using Type=MatrixDimension<M,N>;
};


template <typename MatrixA,typename MatrixB>
struct MultMatrixResult
{
    using MatrixStoragePolicyA=typename MatrixA::TypeMatrixStoragePolicy;
    using MatrixStoragePolicyB=typename MatrixB::TypeMatrixStoragePolicy;
    using TypeDimension=typename MultDimensionTraitResult<typename MatrixA::TypeDimension,typename MatrixB::TypeDimension>::Type;
    using TypeMatrixStoragePolicyFixed=MatrixStoragePolicyFixed<
            typename MatrixStoragePolicyA::Type,
            TypeDimension::size>;

    using T=typename MatrixA::Type;
    using Type=__Matrix<T,TypeDimension,MatrixStoragePolicyFixed>;
};

template <typename MatrixA,typename MatrixB>
struct SumMatrixResult
{
    using MatrixStoragePolicyA=typename MatrixA::TypeMatrixStoragePolicy;
    using MatrixStoragePolicyB=typename MatrixB::TypeMatrixStoragePolicy;
    using TypeDimension=typename SumDimensionTraitResult<typename MatrixA::TypeDimension,typename MatrixB::TypeDimension>::Type;
    using TypeMatrixStoragePolicyFixed=MatrixStoragePolicyFixed<
            typename MatrixStoragePolicyA::Type,
            TypeDimension::size>;

    using T=typename MatrixA::Type;
    using Type=__Matrix<T,TypeDimension,MatrixStoragePolicyFixed>;
};


template <typename MatrixA,typename MatrixB>
struct NodeGenericMatrixMultMatrixResult
{
    using TypeMatrix=typename MultMatrixResult<MatrixA,MatrixB>::Type;
    using TypeStorage=typename TypeMatrix::TypeMatrixStoragePolicy;
    using Type=NodeGeneric <typename MatrixA::Type,TypeMatrix>;
};

template <typename MatrixA,typename MatrixB>
struct NodeAddMatrixAddMatrixResult
{
    using Type=NodeAdd<typename MatrixA::Type,MatrixA,MatrixB>;
};

template <typename MatrixA,typename T>
struct NodeAddMatrixAddScalarResult
{
    using Type=NodeAdd<typename MatrixA::Type,MatrixA,NodeScalar<T>>;
};

template <typename MatrixA,typename MatrixB>
struct NodeGenericMatrixAddMatrixResult
{
    using TypeNodeAdd=typename NodeAddMatrixAddMatrixResult<MatrixA,MatrixB>::Type;
    using Type=NodeGeneric<typename MatrixA::Type,TypeNodeAdd>;
};

template <typename MatrixA,typename T>
struct NodeGenericMatrixAddScalarResult
{
    using TypeNodeAdd=typename NodeAddMatrixAddScalarResult<MatrixA,T>::Type;
    using Type=NodeGeneric<typename MatrixA::Type,TypeNodeAdd>;
};

template <typename MatrixA,typename T>
struct NodeMultMatrixMultScalarResult
{
    using Type=NodeMult<typename MatrixA::Type,MatrixA,NodeScalar<T>>;
};

template <typename MatrixA,typename T>
struct NodeGenericMatrixMultScalarResult
{
    using TypeNodeMult=typename NodeMultMatrixMultScalarResult<MatrixA,T>::Type;
    using Type=NodeGeneric<typename MatrixA::Type,TypeNodeMult>;
};

template <typename MatrixA,typename MatrixB>
struct MultStorageResult
{
    using Type=typename MultMatrixResult<MatrixA,MatrixB>::Type::TypeMatrixStoragePolicy;
};

template<typename MatrixOpResult>
struct MatrixOpResultTrait
{
    using Type=MatrixOpResult;
    static const MatrixOpResult& getNode(MatrixOpResult const &op)
    {
        return op;
    }
};

template<typename T,typename TypeMatrix>
struct MatrixOpResultTrait<NodeGeneric<T,TypeMatrix>>
{
    using Type=TypeMatrix;
    static const  TypeMatrix& getNode(NodeGeneric<T,TypeMatrix> const  &op)
    {
        return op.getNode();
    }
};

template<typename Matrix>
struct MatrixTrait;


template<typename T,size_vt M, size_vt N>
struct MatrixTrait<__Matrix<T,grbus::MatrixDimension<M,N>,grbus::MatrixStoragePolicyFixed>>
{
    using Type=__Matrix<T,grbus::MatrixDimension<M,N>,grbus::MatrixStoragePolicyFixed>;
};


    template<typename T,typename ListColsCurrent,
            typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
    struct MatrixAdj;
/**
 *
             n-1
             --         k+j
    det(M) = \   M  (-1)    |M__|
             /    kj        | kj|
             --
             j=0
 *
 */

    template<typename T,typename ListColsCurrent,
            typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
    struct MatrixAdjSum
    {
        static T result(Storage &s)
        {
#ifdef DETERM_DEBUG
            std::cout<<"MatrixAdjSum#1 col: "<<Front<ListColumn>::value<<std::endl;
        std::cout<<"MatrixAdjSum#1 row: "<<Front<ListRow>::value<<std::endl;
        std::cout<<"MatrixAdjSum#1 els: "<<Front<ListColsCurrent>::value<<std::endl<<std::endl;
#endif
            return s.el(Front<ListRow>::value,Front<ListColumn>::value)
                   *MatrixAdj<T,ListColsCurrent,ListColumn,ListRowsCurrent,ListRow,Storage>::result(s)+
                   MatrixAdjSum<T,ListColsCurrent,PopFront<ListColumn>,ListRowsCurrent,ListRow,Storage>::result(s);
        }
    };

    /**
     * Case 2 end of sum recursion
     */
    template<typename T,typename ListElType,
            typename ListColsCurrent,typename ListRowsCurrent,typename ListRow,typename Storage>
    struct MatrixAdjSum<T,ListColsCurrent,Typelist<ListElType>,ListRowsCurrent,ListRow,Storage>
{
    static T result(Storage &s)
    {
#ifdef DETERM_DEBUG
        std::cout<<"MatrixAdjSum#2 col: "<<Front<Typelist<ListElType>>::value<<std::endl;
        std::cout<<"MatrixAdjSum#2 row: "<<Front<ListRow>::value<<std::endl;
        std::cout<<"MatrixAdjSum#2 els: "<<Front<ListColsCurrent>::value<<std::endl<<std::endl;
#endif
        return  s.el(Front<ListRow>::value,Front<Typelist<ListElType>>::value)*
                MatrixAdj<T,ListColsCurrent,Typelist<ListElType>,ListRowsCurrent,ListRow,Storage>::result(s);
    }
};

/**
 * Case 3 sum of single element
 */
template<typename T,typename ListElType,
        typename ListRowsCurrent,typename ListRow,typename Storage>
struct MatrixAdjSum<T,Typelist<ListElType>,Typelist<ListElType>,ListRowsCurrent,ListRow,Storage>
{
static T result(Storage &s)
{
#ifdef DETERM_DEBUG
    std::cout<<"MatrixAdjSum#3 col: "<<Front<Typelist<ListElType>>::value<<std::endl;
            std::cout<<"MatrixAdjSum#3 row: "<<Front<ListRow>::value<<std::endl;
            std::cout<<"MatrixAdjSum#3 els: "<<Front<Typelist<ListElType>>::value<<std::endl<<std::endl;
#endif
    return  s.el(Front<ListRow>::value,Front<Typelist<ListElType>>::value);
}
};

template<typename T,typename ListColsCurrent,
        typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
struct MatrixAdj
{
    static T result(Storage &s)
    {
#ifdef DETERM_DEBUG
        std::cout<<"MatrixAdj#1 col: "<<Front<ListColumn>::value<<std::endl;
        std::cout<<"MatrixAdj#1 row: "<<Front<ListRow>::value<<std::endl;
        std::cout<<"MatrixAdj#1 els: "<<Front<ListColsCurrent>::value<<std::endl;
#endif
        using ListColsReduced=Remove<ListColsCurrent,Front<ListColumn>>;
        using ListRowsReduced=Remove<ListRowsCurrent,Front<ListRow>>;
#ifdef DETERM_DEBUG
        std::cout<<"MatrixAdj#1 red col: "<<Front<ListColsReduced>::value<<std::endl;
        std::cout<<"MatrixAdj#1 red row: "<<Front<ListRowsReduced>::value<<std::endl;
        std::cout<<"MatrixAdj#1 pow col: "<<IndexOfT<ListColsCurrent,Front<ListColumn>>::value<<std::endl;
        std::cout<<"MatrixAdj#1 pow row: "<<IndexOfT<ListRowsCurrent,Front<ListRow>>::value<<std::endl<<std::endl;
#endif
        return Pow<int_vt ,-1,(IndexOfT<ListColsCurrent,Front<ListColumn>>::value
                                                                          +IndexOfT<ListRowsCurrent,Front<ListRow>>::value)>::value
               *MatrixAdjSum<T,ListColsReduced,ListColsReduced,ListRowsReduced,PopFront<ListRow>,Storage>::result(s);
    }
};

template<typename T,typename ListElType,
        typename ListColumn,typename ListRowsCurrent,typename ListRow,typename Storage>
struct MatrixAdj<T,Typelist<ListElType>,ListColumn,ListRowsCurrent,ListRow,Storage>
{
static T result(Storage &s)
{
#ifdef DETERM_DEBUG
    std::cout<<"MatrixAdj#2 col: "<<Front<ListColumn>::value<<std::endl;
        std::cout<<"MatrixAdj#2 row: "<<Front<ListRow>::value<<std::endl;
        std::cout<<"MatrixAdj#2 els: "<<Front<Typelist<ListElType>>::value<<std::endl;
#endif
    return  s.el(Front<ListRow>::value,Front<ListColumn>::value);
}
};

template <typename Storage,size_vt Row,size_vt Col>
struct AdjRowCol
{
    static typename Storage::Type result(Storage &s)
    {
        static_assert(Storage::TypeDimension::order==2);
        static_assert(Storage::TypeDimension::firstDim==Storage::TypeDimension::secondDim);

        using ListN=CTTypelistN<size_vt ,Storage::TypeDimension::firstDim>;
        using ListCols=Prepend<Remove<ListN,std::integral_constant<size_vt,Col>>,
        std::integral_constant<size_vt,Col>>;
        using ListRows=Prepend<Remove<ListN,std::integral_constant<size_vt,Row>>,
        std::integral_constant<size_vt,Row>>;

        return grbus_operation_trait::MatrixAdj
                <typename Storage::Type,ListN,ListCols,ListN,ListRows,Storage>::result(s);
    }
};

template<typename Storage,uint_vt N>
struct Cofactor
{
    static void result(Storage &from,Storage &to)
    {
        constexpr uint_vt row=(N-1)/Storage::TypeDimension::firstDim;
        constexpr uint_vt col=(N-1)%Storage::TypeDimension::secondDim;
#ifdef DETERM_DEBUG
        std::cout<<"r"<<row<<"col"<<col<<"v"<<AdjRowCol<Storage,row,col>::result(from)<<std::endl;
#endif
        to(row,col)=AdjRowCol<Storage,row,col>::result(from);
        Cofactor<Storage,N-1>::result(from,to);
    }
};

template<typename Storage>
struct Cofactor<Storage,0>
{
    static void result(Storage &from,Storage &to)
    {
        to(0,0)=AdjRowCol<Storage,0,0>::result(from);
    }
};


}
#endif //GRAPHIC_MATRIX_TRAIT_HPP
