//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_insert(Iter begin,Iter end, Compare cmp={})
{
    auto s=begin+1;
    using keyType=typename std::iterator_traits<Iter>::value_type;
    while(s!=end)
    {
        keyType key=*s;
        auto i=s-1;
        ++s;
        // Compare with all elements from right to left.
        while(i>=begin && cmp(key,*i))
        {
            *(i+1)=*i;
            --i;
        }
        *(i+1)=key;
    }
};

#endif //STRUCT_ALG_HEADER_H
