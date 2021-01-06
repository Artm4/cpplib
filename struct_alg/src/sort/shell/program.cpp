//
// Created by art4 on 20.08.20 г..
//

#include "header.h"
#include "lib/common.h"

#define N 10000

int main()
{
    int a[N];
    fillRandInt(a,a+N,N);
    sort_shell(a,a+N);
    //printIter(a,a+N);
}