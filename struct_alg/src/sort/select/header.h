//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>
#include "lib/common.h"

template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_select(Iter begin,Iter end, Compare cmp={})
{
    using keyType=typename std::iterator_traits<Iter>::value_type;

    // select element to exchange
    for(int i=0;begin+i<end;i++)
    {
        int min=i;
        int j;
        // find min from [i+1,n]
        for(j=i+1;begin+j<end;j++)
        {
            if(cmp(*(begin+min),*(begin+j)))
            {
                min=j;
            }
        }
        // exchange selected with min
        exchange(begin,i,min);
    }
};

#endif //STRUCT_ALG_HEADER_H
