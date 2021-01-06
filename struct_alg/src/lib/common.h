//
// Created by art4 on 4.01.21 г..
//

#ifndef STRUCT_ALG_COMMON_H
#define STRUCT_ALG_COMMON_H
#include <algorithm>
#include <unordered_set>
#include <iostream>

template<typename Iter>
void printIter(Iter begin,Iter end)
{
    auto i=begin;
    while(i!=end)
    {
        std::cout<<*(i)<<",";
        i++;
    }
    std::cout<<std::endl;
}

template<typename Iter>
inline void exchange(Iter a,int i,int j)
{
    using keyType=typename std::iterator_traits<Iter>::value_type;
    keyType temp=*(a+i);
    *(a+i)=*(a+j);
    *(a+j)=temp;
}

template<typename Iter>
inline void exchange(Iter a,Iter b)
{
    using keyType=typename std::iterator_traits<Iter>::value_type;
    keyType temp=*(a);
    *(a)=*(b);
    *(b)=temp;
}

template<typename Iter>
void fillRandInt(Iter begin,Iter end,int max)
{
    using keyType=typename std::iterator_traits<Iter>::value_type;
    static_assert(std::is_integral<keyType>::value);
    srand(time(NULL));

    auto i=begin;
    while(i!=end)
    {
        *(i)=rand()%max;
        i++;
    }
}
#endif //STRUCT_ALG_COMMON_H
