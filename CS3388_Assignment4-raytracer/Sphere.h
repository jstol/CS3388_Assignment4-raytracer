//
//  Sphere.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef CS3388_Assignment4_raytracer_Sphere_h
#define CS3388_Assignment4_raytracer_Sphere_h

#include "Object.h"
#include "Ray.h"

class Sphere : public Object{
public:
	Vector position;
    double radius;
    Colour colour;
    
	Sphere();
	Sphere(Vector, double, Colour);
    
    // Methods
    double findIntersectionDistance(Ray ray);
    Vector getNormalAtPoint(Vector pt);
};

Sphere::Sphere() : Object() {
    // Default position at origin; default colour black
	position = Vector(0,0,0);
    radius = 1;
}

Sphere::Sphere(Vector p, double r, Colour c) : Object(c) {
	position = p;
    radius = r;
}

double Sphere::findIntersectionDistance(Ray ray){
    Sphere sphere = (*this);
    
    double a = 1; // normalized
    double b = (2*(ray.origin.x - sphere.position.x)*ray.direction.x) + (2*(ray.origin.y - sphere.position.y)*ray.direction.y) + (2*(ray.origin.z - sphere.position.z)*ray.direction.z);
    double c = pow(ray.origin.x - sphere.position.x, 2) + pow(ray.origin.y - sphere.position.y, 2) + pow(ray.origin.z - sphere.position.z, 2) - (radius*radius);
    
    double discriminant = b*b - 4*c;
    
    if (discriminant > 0) {
        /// the ray intersects the sphere
        
        // the first root
        double root_1 = ((-1*b - sqrt(discriminant))/2) - 0.000001;
        
        if (root_1 > 0) {
            // the first root is the smallest positive root
            return root_1;
        }
        else {
            // the second root is the smallest positive root
            double root_2 = ((sqrt(discriminant) - b)/2) - 0.000001;
            return root_2;
        }
    }
    else {
        // the ray missed the sphere
        return -1;
    }
}

Vector Sphere::getNormalAtPoint(Vector pt){
    return Vector(0,0,0);
}

#endif
