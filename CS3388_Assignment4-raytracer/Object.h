//
//  Object.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
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

Object::Object(){
    colour = Colour(0.0,0.0,0.0,0.0);
}

Object::Object(Colour c){
    colour = c;
}

double Object::findIntersectionDistance(Ray ray){
    return -1;
}

Vector Object::getNormalAtPoint(Vector pt){
    return Vector(0,0,0);
}

#endif /* defined(__CS3388_Assignment4_raytracer__Object__) */
