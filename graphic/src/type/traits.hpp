//
// Created by artyom on 10/3/19.
//

#ifndef GRAPHIC_TRAITS_HPP
#define GRAPHIC_TRAITS_HPP

#include <type_traits>
#include "primitive.h"

namespace grbus
{
    template <template <uint_vt... Dimensions> class T,uint_vt... Rest>
    struct RemoveSecondPackArg
    {
        template<uint_vt First,uint_vt Second,uint_vt... RestT>
        static T<First,RestT...>  test(void*);

        template<uint_vt First>
        static  T<First> test(...);

        using type=decltype(test<Rest...>(nullptr));
    };


    template <template <uint_vt... Dimensions> class T,uint_vt... Rest>
    struct RemoveFirstPackArg
    {
        template<uint_vt First,uint_vt... RestT>
        static T<RestT...>  test(void*);

        template<uint_vt First>
        static  T<First> test(...);

        using type=decltype(test<Rest...>(nullptr));
    };

    template<size_vt N>
    using size_constant=std::integral_constant<size_vt,N>;


    /*
     * Typelist definition
     */
    template<typename... Types>
    struct Typelist
    {

    };

    template<typename List>
    struct FrontT;

    template<typename Head,typename... Tail >
    struct FrontT<Typelist<Head,Tail...>>
    {
        using Type=Head;
    };

    template<typename List>
    using Front=typename FrontT<List>::Type;

    template<typename List>
    struct PopFrontT;

    template<typename Head,typename... Tail >
    struct PopFrontT<Typelist<Head,Tail...>>
    {
        using Type=Typelist<Tail...>;
    };

    template<typename List>
    using PopFront=typename PopFrontT<List>::Type;


    template<typename List,typename T>
    struct PushBackT;

    template<typename... Elements,typename T>
    struct PushBackT<Typelist<Elements...>,T>
    {
        using Type=Typelist<Elements...,T>;
    };

    template<typename List,typename T>
    using PushBack=typename PushBackT<List,T>::Type;

    template<typename List>
    struct IsEmpty
    {
        static constexpr bool value=false;
    };

    template<>
    struct IsEmpty<Typelist<>>
    {
        static constexpr bool value=true;
    };

    template<typename List>
    struct SizeT;

    template<>
    struct SizeT<Typelist<>>
    {
        static constexpr size_vt value=0;
    };

    template<typename Head,typename... Tail>
    struct SizeT<Typelist<Head,Tail...>>
    {
        static constexpr size_vt value=1+SizeT<Typelist<Tail...>>::value;
    };


    template<typename List, size_vt N>
    class NthElementT : public NthElementT<PopFront<List>, N-1>
    {
    };

    // basis case:
    template<typename List>
    class NthElementT<List, 0> : public FrontT<List>
    {
    };

    template<typename List, unsigned N>
    using NthElement = typename NthElementT<List, N>::Type;

    template <typename ListA,typename ListAB>
    struct JoinT;

    template <typename... ElemntsA,typename... ElemntsB>
    struct JoinT<Typelist<ElemntsA...>,Typelist<ElemntsB...>>
    {
        using Type=Typelist<ElemntsA...,ElemntsB...>;
    };

    template <typename ListA,typename ListB>
    using Join=typename JoinT<ListA,ListB>::Type;

    template <typename List,typename T>
    struct PrependT;

    template <typename... Elements,typename T>
    struct PrependT<Typelist<Elements...>,T>
    {
        using Type=Typelist<T,Elements...>;
    };

    template <typename List,typename T>
    using Prepend=typename PrependT<List,T>::Type;

    template <typename List,typename T>
    struct RemoveT;

    template <typename T>
    struct RemoveT<Typelist<>,T>
    {
        using Type=Typelist<>;
    };

    template <typename T>
    struct RemoveT<Typelist<T>,T>
    {
        using Type=Typelist<>;
    };

    template <typename T,typename... Tail>
    struct RemoveT<Typelist<T,Tail...>,T>
    {
        using Type=Typelist<Tail...>;
    };

    template <typename T,typename Head,typename... Tail>
    struct RemoveT<Typelist<Head,Tail...>,T>
    {
        using Type=Prepend<typename RemoveT<Typelist<Tail...>,T>::Type,Head>;
    };

    template <typename List,typename T>
    using Remove=typename RemoveT<List,T>::Type;

    template <typename List,typename T>
    struct IndexOfT;

    template <typename T>
    struct IndexOfT<Typelist<>,T>
    {
        static constexpr int_vt value=-1;
    };

    template <typename T>
    struct IndexOfT<Typelist<T>,T>
    {
        static constexpr int_vt value=0;
    };

    template <typename T,typename... Tail>
    struct IndexOfT<Typelist<T,Tail...>,T>
    {
        static constexpr int_vt value=0;
    };

    template <typename T,typename Head,typename... Tail>
    struct IndexOfT<Typelist<Head,Tail...>,T>
    {
        static constexpr int_vt value=1+IndexOfT<Typelist<Tail...>,T>::value;
    };

    template <typename List>
    struct ReverseT
    {
        using Type=PushBack<typename ReverseT<PopFront<List>>::Type ,Front<List>>;
    };

    template <>
    struct ReverseT<Typelist<>>
    {
        using Type=Typelist<>;
    };

    template <typename List>
    using Reverse=typename ReverseT<List>::Type;


    template<typename T, T... Values>
    using CTTypelist = Typelist<std::integral_constant<T, Values>...>;

    template<typename T,uint_vt N>
    struct CTTypelistNT
    {
        using Type=PushBack<
                typename CTTypelistNT<T,N-1>::Type,std::integral_constant<T,N-1>>;
    };

    template<typename T>
    struct CTTypelistNT<T,0>
    {
        using Type=Typelist<>;
    };

    template <typename T,uint_vt N>
    using CTTypelistN=typename CTTypelistNT<T,N>::Type;


}

#endif //GRAPHIC_TRAITS_HPP
