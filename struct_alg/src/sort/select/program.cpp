//
// Created by art4 on 20.08.20 г..
//

#include "header.h"
#include "lib/common.h"

#define N 10000

bool cmp(int a,int b)
{return a<b;}


int main()
{
    int a[N];
    fillRandInt(a,a+N,N);
    sort_select(a,a+N,[](int a,int b){return a>b;});
    //printIter(a,a+N);
    //sort_select(a,a+N,cmp);
    //printIter(a,a+3);
}