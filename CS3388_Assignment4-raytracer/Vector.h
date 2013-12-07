//
//  Vector.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef __CS3388_Assignment4_raytracer___Vector__
#define __CS3388_Assignment4_raytracer___Vector__

#include <iostream>

class Vector{
public:
    double x,y,z;
    Vector();
    Vector(const Vector &v);
    Vector(double i,double j,double k);
    
    // Vector methods
    double getMagnitude();
    double dot(Vector v);
    Vector cross(Vector v);
    Vector plus(Vector v);
    Vector minus(Vector v);
    Vector scale(double k);
    Vector normalize();
};

Vector::Vector (){
    x = y = z = 0;
}
Vector::Vector(double i, double j, double k){
    x=i;
    y=j;
    z=k;
}
Vector::Vector(const Vector &v){
    x = v.x;
    y = v.y;
    z = v.z;
}

double Vector::getMagnitude(){
    return sqrt((x*x)+(y*y)+(z*z));
}

double Vector::dot(Vector v){
    return x*v.x + y*v.y + z*v.z;
}

Vector Vector::cross(Vector v){
    return Vector(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

Vector Vector::plus(Vector v){
    return Vector(x+v.x, y+v.y, z+v.z);
}

Vector Vector::minus(Vector v){
    return Vector(x-v.x,y-v.y,z-v.z);
}

Vector Vector::scale(double k){
    return Vector(x*k, y*k, z*k);
}

Vector Vector::normalize(){
    double magnitude = this->getMagnitude();
    return Vector(x/magnitude,y/magnitude,z/magnitude);
}

#endif /* defined(__CS3388_Assignment4_raytracer___Vector__) */
