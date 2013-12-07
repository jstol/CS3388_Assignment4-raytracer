//
//  Plane.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef CS3388_Assignment4_raytracer_Plane_h
#define CS3388_Assignment4_raytracer_Plane_h

#include "Object.h"
#include "Vector.h"

class Plane : Object{
public:
	Vector position;
    Vector a;
    Vector b;
    Vector normal;
    Colour colour;
    double size;
    
	Plane();
	Plane(Vector, Vector, Vector, Colour, double);
    
    // Methods
    double findIntersectionDistance(Ray ray);
};

Plane::Plane() : Object() {
    // Default is X & Y plane; default colour black
	position = Vector(0,0,0);
    a = Vector(1,0,0);
    b = Vector(0,1,0);
    normal = a.cross(b);
    size = 1;
}

Plane::Plane(Vector p, Vector v1, Vector v2, Colour c, double s) : Object(c) {
	position = p;
    a = v1;
    b = v2;
    normal = a.cross(b);
    size = s;
}

double Plane::findIntersectionDistance(Ray ray){
    Plane plane = (*this);
    double origin_distance = position.getMagnitude();
    double e2 = plane.normal.dot(ray.origin.plus(plane.normal.scale(-origin_distance)));
    double c2 = ray.direction.dot(normal);
    
    // If the ray makes a 90 degree angle with the normal, must be parallel, so return -1
    if (c2 == 0) return -1;
    // Otherwise, return the distance
    else{
        double distance = -e2/c2;
        if (distance > size) return -1;
        // Return the distance from the ray origin to the point of intersection
        return -e2/c2;
    }
}

#endif
