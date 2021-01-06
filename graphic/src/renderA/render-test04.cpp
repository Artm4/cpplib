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
#include <renderA/render/transform.h>

namespace grbus {

}

using namespace grbus;

int main()
{
    Vector vb1{0,0,1};
    Transform t1;
    t1.rotateDeg(vb1,15);
    t1.rotateDeg(vb1,45);

    t1.translate({1,1,0});

    Vector vt1{1,0,0};

    Vector r1=t1.apply(vt1);

    printMatrixMN(r1);

    Vector t1i{-1,-1,0};
    real_vt b=2;
    t1i=2*vt1;
    printMatrixMN(t1i);

    std::cout<<"Quaternion identity"<<std::endl;
    Quaternion q{1,0,0,1};
    Quaternion qt=q.inv();

    Quaternion qr=q*qt;
    printMatrixMN(q*qt);
}