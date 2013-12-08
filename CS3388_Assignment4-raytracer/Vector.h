//
//  Vector.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold all data related to 3D vectors.
//  It also has method definitions for operating with vectors.
//
//  Created by Jake on 2013-12-06.
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

// Default Constructor
// Input: none
// Output: N/A
Vector::Vector (){
    x = y = z = 0;
}

// Constructor that allows for initial x,y,z values to be initialized
// Input: i,j,k (double)
// Output: N/A
Vector::Vector(double i, double j, double k){
    x=i;
    y=j;
    z=k;
}

// Copy constructor
// Input: v (const Vector&)
// Output: N/A
Vector::Vector(const Vector &v){
    x = v.x;
    y = v.y;
    z = v.z;
}

// Function to return the magniitude of the vector
// Input: none
// Output: the magnitude of the vector (double)
double Vector::getMagnitude(){
    return sqrt((x*x)+(y*y)+(z*z));
}

// Function to compute the dot product with a vector
// Input: v (Vector)
// Output: the dot product (double)
double Vector::dot(Vector v){
    return x*v.x + y*v.y + z*v.z;
}

// Function to compute the cross product with a vector
// Input: v (Vector)
// Output: the cross product (Vector)
Vector Vector::cross(Vector v){
    return Vector(y*v.z-z*v.y, z*v.x-x*v.z, x*v.y-y*v.x);
}

// Function to add a vector
// Input: v (Vector)
// Output: the resulting vector (Vector)
Vector Vector::plus(Vector v){
    return Vector(x+v.x, y+v.y, z+v.z);
}

// Function to subtract a vector
// Input: v (Vector)
// Output: the resulting vector (Vector)
Vector Vector::minus(Vector v){
    return Vector(x-v.x,y-v.y,z-v.z);
}

// Function to scale the vector by a scalar
// Input: k (double)
// Output: the resulting vector (Vector)
Vector Vector::scale(double k){
    return Vector(x*k, y*k, z*k);
}

// Function to normalize the vector
// Input: none
// Output: the resulting vector (Vector)
Vector Vector::normalize(){
    double magnitude = this->getMagnitude();
    return Vector(x/magnitude,y/magnitude,z/magnitude);
}

#endif /* defined(__CS3388_Assignment4_raytracer___Vector__) */
