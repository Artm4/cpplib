//
// Created by art4 on 20.08.20 г..
//

#include <vector>
#include "header.h"
#include "lib/common.h"

#define N 10000
using namespace stde;
int main()
{
    int a[N];
    fillRandInt(a,a+N,N);
    sort_quick(a,a+N);
    //printIter(a,a+N);
}