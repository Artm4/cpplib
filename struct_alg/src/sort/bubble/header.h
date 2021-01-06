//
// Created by art4 on 23.12.20 г..
//

#ifndef STRUCT_ALG_HEADER_H
#define STRUCT_ALG_HEADER_H
#include <algorithm>
#include <unordered_set>
#include "lib/common.h"


template<typename Iter,typename Compare=std::less<typename std::iterator_traits<Iter>::value_type>>
void sort_bubble(Iter begin,Iter end, Compare cmp={})
{
    using keyType=typename std::iterator_traits<Iter>::value_type;

    for(int i=0;begin+i<end;i++)
    {
        // bubble next min/max element to the end-i-1 position
        for(int j=0;begin+j<end-i-1;j++)
        {
            if(cmp(*(begin+j),*(begin+j+1)))
            {
                exchange(begin,j,j+1);
            }
        }
    }
};

#endif //STRUCT_ALG_HEADER_H
