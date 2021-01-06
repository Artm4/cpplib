//
// Created by art4 on 20.08.20 г..
//

#include <vector>
#include "header.h"
#include "lib/common.h"

#define N 10000

void testVector()
{
    std::vector<int> a(N);
    fillRandInt(a.begin(),a.end(),N);
    sort_merge(a.begin(),a.end());
    printIter(a.begin(),a.end());
}

int main()
{
    int a[N];
    fillRandInt(a,a+N,N);
    sort_merge(a,a+N);
    printIter(a,a+N);
}