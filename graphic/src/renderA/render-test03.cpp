//
// Created by artyom on 11/21/19.
//

//
// Created by artyom on 11/5/19.
//

#include <iostream>

#include <string.h>
#include <chrono>
#include <render/gi.h>

namespace grbus {




}


struct SomeA
{
    int a;
};

struct SomeB
{
    float b;

    SomeB()=default;

    SomeB(float b) : b(b) {}

    SomeB(SomeA a):b{a.a}{}
};

void printSome(SomeB b)
{
    std::cout<<b.b<<std::endl;
}


template<typename MatrixOpResultType>
struct MatrixOpResultTrait;




using namespace grbus;

int main()
{
    Matrix m1={
        {1,2,3},
        {1,2,3},
        {1,2,3}
    };

    Vector v1{1,2,3};


    Vector r1=m1*v1;


    printMatrixMN((m1*v1));
    SomeA a{1};
    SomeB b{2};

    printSome(a);

}