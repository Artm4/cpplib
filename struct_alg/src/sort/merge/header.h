//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>
#include <memory>

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
static void merge(Iter begin,Iter middle,Iter end, Compare cmp={});

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_merge(Iter begin,Iter end, Compare cmp={})
{
    // should check inner indexes not out of bound end index
    if(begin<end-1)
    {
        using diffType=typename std::iterator_traits<Iter>::difference_type;
        diffType n=end-begin;
        Iter middle=begin+n/2;
        //middle exclusive
        sort_merge(begin,middle,cmp);
        //middle inclusive
        sort_merge(middle,end,cmp);
        merge(begin,middle,end,cmp);
    }
}


template<typename Iter,typename Compare>
static void merge(Iter begin,Iter middle,Iter end, Compare cmp)
{
    using diffType=typename std::iterator_traits<Iter>::difference_type;
    using valueType=typename std::iterator_traits<Iter>::value_type;

    diffType n1=middle-begin;
    diffType n2=end-middle;
    std::shared_ptr<valueType[]> lp{new valueType[n1]};
    std::shared_ptr<valueType[]> rp{new valueType[n2]};

    std::uninitialized_copy(begin,middle,lp.get());
    std::uninitialized_copy(middle,end,rp.get());

    auto k=begin;
    int i=0,j=0;
    while(i<n1 && j<n2)
    {
        if(cmp(lp[i],rp[j]))
        {
            *k=lp[i];
            i++;
        }
        else
        {
            *k=rp[j];
            j++;
        }
        k++;
    }

    while(i<n1)
    {
        *k=lp[i];
        i++;
        k++;
    }
    while(j<n2)
    {
        *k=rp[j];
        j++;
        k++;
    }
};

#endif //STRUCT_ALG_HEADER_H
