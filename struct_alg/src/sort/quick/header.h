//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>
#include <memory>
#include <lib/common.h>

namespace stde{

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
static Iter partition(Iter begin,Iter end, Compare cmp={});

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_quick(Iter begin,Iter end, Compare cmp={})
{
    if(begin<end-1)
    {
        auto q=stde::partition(begin,end,cmp);
        // q exclusive
        sort_quick(begin,q);
        // q exclusive
        sort_quick(q+1,end);
    }
}

template<typename Iter,typename Compare>
static Iter partition(Iter begin,Iter end, Compare cmp)
{
    using valueType=typename std::iterator_traits<Iter>::value_type;
    auto x=(end-1);
    auto i=begin-1;
    for(auto j=begin;j<x;j++)
    {
        if(cmp(*j,*x))
        {
            i=i+1;
            exchange(j,i);
        }
    }
    exchange(x,(i+1));
    return i+1;
}

}
#endif //STRUCT_ALG_HEADER_H
