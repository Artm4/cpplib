//
// Created by art4 on 14.05.20 г..
//

#include <stdio.h>
#include <string.h>
#include <limits.h>

typedef unsigned char* byte_repr;

void printInt(int a);

void show_bytes(byte_repr bytes,int size);

void printInt(int a)
{
    show_bytes((byte_repr) &a,sizeof(a));
}

void printFloat(float a)
{
    show_bytes((byte_repr) &a,sizeof(a));
}

void printPointer(void* a)
{
    show_bytes((byte_repr) &a,sizeof(a));
}

void show_bytes(byte_repr bytes,int size)
{
    for(int i=0;i<size;i++)
    {
        printf("%.2x ",bytes[i]);
    }
    printf("\n");
}



void test_bytes(int val)
{
    int ival = val;
    float fval = (float) ival;
    int *pval = &ival;
    printInt(ival);
    printFloat(fval);
    printPointer(pval);
    const char *s = "abcdef";
    show_bytes((byte_repr) s, strlen(s));
}

void test_min_max()
{
    unsigned int ru=-2147483647-1U;
    int rs=-2147483647-1U<2147483647;
    int maxs=INT_MAX;
    int mins=INT_MIN;
    unsigned int maxu=UINT_MAX;
}

void testBinrepr()
{
    test_bytes(0x7);
    test_min_max();
}


