//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_shell(Iter begin,Iter end, Compare cmp={})
{

    using keyType=typename std::iterator_traits<Iter>::value_type;
    using diffType=typename std::iterator_traits<Iter>::difference_type;

    diffType size=end-begin;
    int h;
    // pick h, it is empiric value
    for (h=1;h < size/3; h = 3*h + 1);
    // loop for h=[h,h/3,h/9 ... 1]
    for(;h>0;h/=3)
    {
        auto s = begin + h;
        while (s < end)
        {
            keyType key = *s;
            auto i = s - h;
            s=s+h;
            // Compare with all elements from right to left.
            while (i >= begin && cmp(key, *i))
            {
                *(i + h) = *i;
                i = i - h;
            }
            *(i + h) = key;
        }
    }
};

#endif //STRUCT_ALG_HEADER_H
