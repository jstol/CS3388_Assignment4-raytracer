//
//  Plane.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold all data and methods related to 3D plane objects.
//
//  Created by Jake on 2013-12-06.
//

#ifndef CS3388_Assignment4_raytracer_Plane_h
#define CS3388_Assignment4_raytracer_Plane_h

#include "Object.h"
#include "Vector.h"

#define PREC 0.000001

class Plane : public Object{
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
    Vector getNormalAtPoint(Vector pt);
};

// Default constructor
// Input: none
// Output: N/A
Plane::Plane() : Object() {
    // Default is X & Y plane; default colour black
	position = Vector(0,0,0);
    a = Vector(1,0,0);
    b = Vector(0,1,0);
    normal = a.cross(b);
    size = 1;
}

// Constructor that allows for the plane's position, defining vectors (a and b), colour, and size to be specified.
// Input: p, v1, v2 (Vector), c (Colour), s (double)
// Output: N/A
Plane::Plane(Vector p, Vector v1, Vector v2, Colour c, double s) : Object(c) {
	position = p;
    a = v1;
    b = v2;
    normal = a.cross(b);
    size = s;
}

// Function to find the intersection with a ray. If they don't intersect, -1 is returned.
// Input: ray (Ray)
// Output: distance to the object (double)
double Plane::findIntersectionDistance(Ray ray){
    Plane plane = (*this);
    double origin_distance = position.getMagnitude();
    double e = plane.normal.dot(ray.origin.plus(plane.normal.scale(-origin_distance)));
    double c = ray.direction.dot(normal);
    
    // If the ray makes a 90 degree angle with the normal, must be parallel, so return -1
    if (c == 0) return -1;
    // Otherwise, return the distance
    else{
        double ray_distance = -e/c - PREC;
        Vector pt = ray.origin.plus(ray.direction.scale(ray_distance));
        double distance_on_plane = position.minus(pt).getMagnitude();
        // Return -1 if the plane is set to be finite and the point actually lies outside of the defined area
        if (distance_on_plane > size) return -1;
        // Return the distance from the ray origin to the point of intersection
        return ray_distance;
    }
}

// Function to calculate the normal on the surface of the object at a given point.
// Input: pt (Vector)
// Out: the normal at pt (Vector)
Vector Plane::getNormalAtPoint(Vector pt){
    return normal;
}

#endif
