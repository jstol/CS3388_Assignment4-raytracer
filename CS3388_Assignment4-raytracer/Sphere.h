//
//  Sphere.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold all data and methods related to 3D sphere objects.
//
//  Created by Jake on 2013-12-06.
//

#ifndef CS3388_Assignment4_raytracer_Sphere_h
#define CS3388_Assignment4_raytracer_Sphere_h

#include "Object.h"
#include "Ray.h"

#define PREC 0.000001

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

// Default constructor
// Input: none
// Output: N/A
Sphere::Sphere() : Object() {
    // Default position at origin; default radius of 1
	position = Vector(0,0,0);
    radius = 1;
}

// Constructor which allows for the sphere's position, radius, and colour to be initialized
// Input: p (Vector), r (double), c (Colour)
// Output: N/A
Sphere::Sphere(Vector p, double r, Colour c) : Object(c) {
	position = p;
    radius = r;
}

// Function to find the intersection with a ray. If they don't intersect, -1 is returned.
// Input: ray (Ray)
// Output: distance to the object (double)
double Sphere::findIntersectionDistance(Ray ray){
    Sphere sphere = (*this);
    double a = 1;
    double b = (2*(ray.origin.x-sphere.position.x)*ray.direction.x) + (2*(ray.origin.y-sphere.position.y)*ray.direction.y) + (2*(ray.origin.z-sphere.position.z)*ray.direction.z);
    double c = pow(ray.origin.x-sphere.position.x, 2) + pow(ray.origin.y-sphere.position.y, 2) + pow(ray.origin.z-sphere.position.z, 2) - (pow(radius, 2));
    
    // Check if the ray intersects with the sphere by finding the discriminant of the quadratic equation a.t^2 + 2.b.t + c = 0
    double discrim = pow(b,2)-4*a*c;
    if (discrim > 0) {
        double first_root = ((-b-sqrt(discrim))/(2*a)) - PREC;
        double second_root = ((-b+sqrt(discrim))/(2*a)) - PREC;
        
        // If the first root is greater than 0, then the distance is the first root
        if (first_root > 0) return first_root;
        // Otherwise the second root is
        else return second_root;
    }
    // Return -1 if it misses it
    else return -1;
}

// Function to get the normal on the sphere at any point
// Input: pt (Vector)
// Output: the resulting normal (Vector)
Vector Sphere::getNormalAtPoint(Vector pt){
    return pt.minus(this->position).normalize();
}

#endif
