//
// Created by art4 on 20.08.20 г..
//
#include <stdio.h>
#include <limits.h>

int tadd_ok(int x,int y)
{
    int result=!(x>0 && y>0 && (x+y)<0)
            && !(x<0 && y<0 && (x+y)>0);
    return result;
}

int tsub_ok(int x,int y)
{
    return tadd_ok(x,-y);
}

int tmult_ok(int x,int y)
{
    int p=x*y;
    return !x || p/x==y;
}

int tmult_ok64(int x,int y)
{
    long long pll=(long long) x*y;
    return pll==(int) pll;
}

void testTAdd()
{
    int intMinAdd=tadd_ok(INT_MIN,-1);
    int intMaxAdd=tadd_ok(INT_MAX,1);
    int intDifSign=tadd_ok(INT_MIN,1);

    printf("intMinAdd: %d\n"
           "intMaxAdd: %d\n"
           "intDifSign: %d\n",intMinAdd,intMaxAdd,intDifSign);
}

void testTMult()
{
    int intMinMul=tmult_ok(INT_MIN,2);
    int intMaxMul=tmult_ok(INT_MAX,2);
    int intMul=tmult_ok(INT_MAX,1);

    printf("intMinMul: %d\n"
           "intMaxMul: %d\n"
           "intMul: %d\n",
           intMinMul,intMaxMul,intMul);

    int intMinMul64=tmult_ok64(INT_MIN,2);
    int intMaxMul64=tmult_ok64(INT_MAX,2);
    int intMul64=tmult_ok64(INT_MAX,1);

    printf("intMinMul64: %d\n"
           "intMaxMul64: %d\n"
           "intMul64: %d\n",
           intMinMul64,intMaxMul64,intMul64);
}


int div16(int x)
{
    int bias=(x>>31) & 0xF;
    return (x+bias) >> 4;
}

void testDiv()
{
    div16(-32);
}

void testExpr()
{
    int x=0;
    int y=0;

    unsigned ux=x;
    unsigned uy=y;
    int resB=((x&7)!=7) || (x<<29<0);

    x=0xFFFF;
    resB=(x*x);
}

void testArithm()
{
    testTAdd();
    testTMult();
    testDiv();
    testExpr();
}
