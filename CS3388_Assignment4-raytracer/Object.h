//
//  Object.h
//  CS3388_Assignment4-raytracer
//
//  This class holds all information for a general 3D object that is to be raytraced.
//
//  Created by Jake on 2013-12-06.
//

#ifndef __CS3388_Assignment4_raytracer__Object__
#define __CS3388_Assignment4_raytracer__Object__

#include "Colour.h"
#include "Ray.h"
#include "Vector.h"

class Object{
public:
    Colour colour;
    Object();
    Object(Colour c);
    
    // Methods
    virtual double findIntersectionDistance(Ray ray);
    virtual Vector getNormalAtPoint(Vector pt);
    
};

// Default object constructor
// Input: none
// Output: none
Object::Object(){
    colour = Colour(0.0,0.0,0.0,0.0);
}

// Object constructor
// Input: c (Colour)
// Output: N/A
Object::Object(Colour c){
    colour = c;
}

// Function to find the intersection with a ray. If they don't intersect, -1 is returned.
// Input: ray (Ray)
// Output: distance to the object (double)
double Object::findIntersectionDistance(Ray ray){
    return -1;
}

// Function to calculate the normal on the surface of the object at a given point.
// Input: pt (Vector)
// Out: the normal at pt (Vector)
Vector Object::getNormalAtPoint(Vector pt){
    return Vector(0,0,0);
}

#endif /* defined(__CS3388_Assignment4_raytracer__Object__) */
