//
// Created by artyom on 11/5/19.
//

#ifndef GRAPHIC_OPERATION_HPP
#define GRAPHIC_OPERATION_HPP

#include "matrix.hpp"
#include "operation_trait.hpp"

namespace grbus
{




using namespace grbus_operation_trait;

template<typename T, typename Node>
struct NodeGeneric {
    static constexpr size_vt size=Node::getSize();

    Node node;

    NodeGeneric(Node const &node) : node(node) {}


    auto get(size_vt index) -> decltype(node.get(index)) const {
        return node.get(index);
    }

    template<typename TB,typename NodeB>
    NodeGeneric<T,Node>& operator=(NodeGeneric<TB,NodeB> gop)
    {
        for(int i=0;i<getSize();i++)
        {
            node.get(i) = gop.get(i);
        }
        return *this;
    }

    template<typename TB,typename NodeB>
    NodeGeneric<T,Node>& operator*=(NodeGeneric<TB,NodeB> gop)
    {
        for(int i=0;i<getSize();i++)
        {
            node.get(i) *= gop.get(i);
        }
        return *this;
    }

    Node& getNode() {
        return node;
    }

    size_vt getSize()
    {
        return node.getSize();
    }

    Node const & getNode() const{
        return node;
    }

    size_vt getSize() const
    {
        return size;
    }
};

template<typename N>
struct NodeScalar {
    // N const& v; leads to loosing temporary scalar value in expression
    N const v;
    static constexpr size_vt size=1;

    NodeScalar(N const &v) : v(v) {}

    N operator[](size_vt index) {
        return v;
    }

    N operator[](size_vt index) const {
        return v;
    }

    N get(size_vt index) {
        return v;
    }

    N get(size_vt index) const {
        return v;
    }

    static constexpr size_vt getSize()
    {
        return 1;
    }
};

template<typename T>
struct NodeTrait
{
    using Type=T const &;
    static constexpr size_vt size=T::size;
};

template<typename T>
struct NodeTrait<NodeScalar<T>>
{
    using Type=NodeScalar<T>;
    static constexpr size_vt size=4;
};


template<typename T,typename U>
struct NodeTraitResult
{
    using TypeMatrix=typename T::TypeMatrix;
};

template<typename T,typename U>
struct NodeTraitResult<NodeScalar<T>,U>
{
    using TypeMatrix=typename U::TypeMatrix;
};

template<typename T,typename U>
struct NodeTraitResult<T,NodeScalar<U>>
{
    using TypeMatrix=typename T::TypeMatrix;
};

template<typename T,typename U>
struct NodeTraitResult<NodeScalar<T>,NodeScalar<U>>
{
    using TypeMatrix=void*;
};

template<typename T, typename NodeA, typename NodeB>
struct NodeAdd {
    typename NodeTrait<NodeA>::Type opA;
    typename NodeTrait<NodeB>::Type opB;
    using TypeMatrix=typename NodeTraitResult<NodeA,NodeB>::TypeMatrix;

    static constexpr size_vt size=TypeMatrix::TypeDimension::size;

    NodeAdd( NodeA const& opA, NodeB const& opB) : opA(opA), opB(opB)
    {}

    T get(size_vt index) const{
        //std::cout<<opA[index]<<": "<<opB[index]<<std::endl;
        return opA.get(index) + opB.get(index);
    }

    MatrixStoragePolicyFixed<T, NodeTrait<NodeA>::size> result() const
    {
        MatrixStoragePolicyFixed<T, NodeTrait<NodeA>::size> result;
        for(int i=0;i<getSize();i++)
        {
            result[i] = opA.get(i) + opB.get(i);
        }
        return result;
    }

    static constexpr size_vt getSize()
    {
        return NodeTrait<NodeA>::size;
    }
};

template<typename T, typename NodeA, typename NodeB>
struct NodeMult {
    typename NodeTrait<NodeA>::Type opA;
    typename NodeTrait<NodeB>::Type opB;
    using TypeMatrix=typename NodeTraitResult<NodeA,NodeB>::TypeMatrix;

    static constexpr size_vt size=TypeMatrix::TypeDimension::size;

    NodeMult( NodeA const& opA, NodeB const& opB) : opA(opA), opB(opB)
    {}

    T get(size_vt index) const{
        //std::cout<<opA[index]<<": "<<opB[index]<<std::endl;
        return opA.get(index) * opB.get(index);
    }


    MatrixStoragePolicyFixed<T, NodeTrait<NodeA>::size> result() const
    {
        MatrixStoragePolicyFixed<T, NodeTrait<NodeA>::size> result;
        for(int i=0;i<getSize();i++)
        {
            result[i] = opA.get(i) * opB.get(i);
        }
        return result;
    }

    static constexpr size_vt getSize()
    {
        return NodeTrait<NodeA>::size;
    }
};


// Matrix + Matrix
template<typename T,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
typename NodeGenericMatrixAddMatrixResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,
__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyB>>::Type
operator+(__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyB> const & b)
{
using TypeMatrixResult=typename NodeAddMatrixAddMatrixResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,
__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyB>>::Type;
TypeMatrixResult goms(a,b);
return goms;
};

// Matrix + T
template<typename T,typename V,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA>
typename NodeGenericMatrixAddScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T>::Type
operator+(const __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> &a,V const & b)
{
using TypeMatrixResult=typename NodeAddMatrixAddScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T
>::Type;
TypeMatrixResult goms(a, static_cast<T const &>(b));
return goms;
};

// T + Matrix
template<typename T,typename V,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA>
typename NodeGenericMatrixAddScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T>::Type
operator+(V const & b,const __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> &a)
{
using TypeMatrixResult=typename NodeAddMatrixAddScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T
>::Type;
TypeMatrixResult goms(a, static_cast<T const &>(b));
return goms;
};

// Generic + Generic
template <typename T, typename NodeA,typename NodeB>
NodeGeneric<T,NodeAdd<T,NodeA,NodeB>>
operator+(NodeGeneric<T,NodeA> const& opA,NodeGeneric<T,NodeB> const& opB)
{
    return NodeAdd<T,NodeA,NodeB>(
            opA.getNode(),opB.getNode()
    );
};

// Generic + Matrix
template<typename T,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA,typename NodeB>
NodeGeneric<T,NodeAdd<T,NodeB,__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>>>
operator+(NodeGeneric<T,NodeB> const& opA, __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const& opB)
{
NodeAdd<T,NodeB,__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>> goms(opA.getNode(),opB);
return goms;
};

// Matrix + Generic
template<typename T,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA,typename NodeB>
NodeGeneric<T,NodeAdd<T,NodeB,__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>>>
operator+(__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const& opB,NodeGeneric<T,NodeB> const& opA)
{
    NodeAdd<T,NodeB,__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>> goms(opA.getNode(),opB);
    return goms;
};

// Generic + T
template<typename T,typename V,typename NodeB>
NodeGeneric<T,NodeAdd<T,NodeB,NodeScalar<T>>>
operator+(NodeGeneric<T,NodeB> const& opA,V const& opB)
{
    NodeAdd<T,NodeB,NodeScalar<T>> goms(opA.getNode(), static_cast<T const &>(opB));
    return goms;
};

// T + Generic
template<typename T,typename V,typename NodeB>
NodeGeneric<T,NodeAdd<T,NodeB,NodeScalar<T>>>
operator+(V const& opB,NodeGeneric<T,NodeB> const& opA)
{
    NodeAdd<T,NodeB,NodeScalar<T>> goms(opA.getNode(), static_cast<T const &>(opB));
    return goms;
};


// Matrix * Matrix as function
template <typename MatrixA,typename MatrixB>
typename MultMatrixResult<MatrixA,MatrixB>::Type
matrixMult(MatrixA &a,MatrixB &b)
{

    using TypeResult=typename MultMatrixResult<MatrixA,MatrixB>::Type;
    TypeResult r;

    constexpr size_vt rowsN=MatrixA::TypeDimension::firstDim;
    constexpr size_vt colsN=MatrixB::TypeDimension::secondDim;
    constexpr size_vt depthN=MatrixA::TypeDimension::secondDim;

    constexpr size_vt colsA=MatrixA::TypeDimension::secondDim;
    constexpr size_vt rowsB=MatrixB::TypeDimension::firstDim;

    static_assert(colsA==rowsB);

    for(size_vt i=0;i<rowsN;i++)
        for(size_vt j=0;j<colsN;j++)
            for(size_vt k=0;k<depthN;k++)
            {
                r(i,j)+=a(i,k)*b(k,j);
            }
    return r;
};


// Matrix * Matrix
template<typename T,size_vt M, size_vt N, size_vt V,size_vt U,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
typename NodeGenericMatrixMultMatrixResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,
        __Matrix<T,MatrixDimension<V,U>,MatrixStoragePolicyB>>::Type
operator*(__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<V,U>,MatrixStoragePolicyB> const & b)
{
    return matrixMult(a,b);
};


// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize(),b.data(),static_cast<T>(0));
};


// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,3> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);

    return s;
};

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize(),b.data(),static_cast<T>(0));
};


// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,3> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);

    return s;
};

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize(),b.data(),static_cast<T>(0));
};


// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,3> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);

    return s;
};

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize(),b.data(), static_cast<T>(0));
};


// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<3,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,3>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,3> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);

    return s;
    };

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize()-1,b.data(),static_cast<T>(0));
};


// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,4> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);
    s[3]=0;

    return s;
};

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize()-1,b.data(),static_cast<T>(0));
};

// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,4> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);
    s[3]=0;

    return s;
};

// Vector * Vector - scalar
    template<typename T,
            template <typename,size_vt> class MatrixStoragePolicyA,
            template <typename,size_vt> class MatrixStoragePolicyB>
    T operator*(__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyB> const & b)
    {
        return std::inner_product(a.data(),a.data()+a.getSize()-1,b.data(),static_cast<T>(0));
    };

// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,4> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);
    s[3]=0;

    return s;
};

// Vector * Vector - scalar
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
T operator*(__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyB> const & b)
{
    return std::inner_product(a.data(),a.data()+a.getSize()-1,b.data(),static_cast<T>(0));
};

// Vector % Vector - vector product
template<typename T,
        template <typename,size_vt> class MatrixStoragePolicyA,
        template <typename,size_vt> class MatrixStoragePolicyB>
__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyFixed>
operator%(__Matrix<T,MatrixDimension<4,1>,MatrixStoragePolicyA> const &a,__Matrix<T,MatrixDimension<1,4>,MatrixStoragePolicyB> const & b)
{
    /*
     * (y*vector.z-z*vector.y,
z*vector.x-x*vector.z,
x*vector.y-y*vector.x);
     */
    MatrixStoragePolicyFixed<T,4> s;
    s[0]=a(1)*b(2)-a(2)*b(1);
    s[1]=a(2)*b(0)-a(0)*b(2);
    s[2]=a(0)*b(1)-a(1)*b(0);
    s[3]=0;

    return s;
};

// Matrix * T
template<typename T,typename V,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA>
typename NodeGenericMatrixMultScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T>::Type
operator*(const __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> &a,V const & b)
{
using TypeMatrixResult=typename NodeMultMatrixMultScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T
>::Type;
TypeMatrixResult goms(a, static_cast<T const &>(b));
return goms;
};

// T * Matrix
template<typename T,typename V,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA>
typename NodeGenericMatrixMultScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T>::Type
operator*(V const & b,const __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> &a)
{
using TypeMatrixResult=typename NodeMultMatrixMultScalarResult<
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>,T
>::Type;
TypeMatrixResult goms(a,static_cast<T const &>(b));
return goms;
};

// Generic * T
template<typename T,typename V,typename NodeB>
NodeGeneric<T,NodeMult<T,NodeB,NodeScalar<T>>>
operator*(NodeGeneric<T,NodeB> const& opA,V const& opB)
{
    NodeMult<T,NodeB,NodeScalar<T>> goms(opA.getNode(), static_cast<T const &>(opB));
    return goms;
};

// T * Generic
template<typename T,typename V,typename NodeB>
NodeGeneric<T,NodeMult<T,NodeB,NodeScalar<T>>>
operator*(V const& opB,NodeGeneric<T,NodeB> const& opA)
{
    NodeMult<T,NodeB,NodeScalar<T>> goms(opA.getNode(), static_cast<T const &>(opB));
    return goms;
};

// Generic * Matrix
template<typename T,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA,typename NodeB>
typename NodeGenericMatrixMultMatrixResult<
        typename NodeB::TypeMatrix,
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>
>::Type
operator*(NodeGeneric<T,NodeB> const& opA, __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const& opB)
{
typename NodeB::TypeMatrix mA;
mA.storage=opA.getNode().result();
return matrixMult(mA,opB);
};

// Matrix * Generic
template<typename T,size_vt M, size_vt N,
        template <typename,size_vt> class MatrixStoragePolicyA,typename NodeB>
typename NodeGenericMatrixMultMatrixResult<
        typename NodeB::TypeMatrix,
        __Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA>
>::Type
operator*(__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const& opB,NodeGeneric<T,NodeB> const& opA)
{
    typename NodeB::TypeMatrix mA;
    mA.storage=opA.getNode().result();
    return matrixMult(mA,opB);
};

template <typename TypeOpResult>
void printMatrixMN(TypeOpResult r)
{
    __printMatrixMN(MatrixOpResultTrait<TypeOpResult>::getNode(r));
}


    template<typename T,size_vt M, size_vt N,
            template <typename,size_vt> class MatrixStoragePolicyA>
void __printMatrixMN(__Matrix<T,MatrixDimension<M,N>,MatrixStoragePolicyA> const &m)
{
    for(int i=0;i<M;i++)
    {
        std::cout<<"[";
        for (int j = 0; j < N; j++)
        {
            std::cout << m(i, j);
            if(j!=N-1){std::cout<<",";}
        }
        std::cout<<"]";
        std::cout<<std::endl;
    }
}



}

#endif //GRAPHIC_OPERATION_HPP
