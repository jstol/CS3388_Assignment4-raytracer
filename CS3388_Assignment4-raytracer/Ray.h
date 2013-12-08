//
//  Ray.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold data related to a ray object.
//
//  Created by Jake on 2013-12-06.
//

#ifndef CS3388_Assignment4_raytracer_Ray_h
#define CS3388_Assignment4_raytracer_Ray_h

class Ray {
public:
    Vector origin, direction;
    Ray();
    Ray(Vector, Vector);
};

// Default constructor
// Input: none
// Output: N/A
Ray::Ray (){
    // Default origin is 0,0,0; Default direction is in the X-Direction
    origin = Vector(0,0,0);
    direction = Vector(1,0,0);
}

// Constructor that allows for the ray to be initialized with origin and direction vectors
// Input: ori,dir (Vector)
// Output: N/A
Ray::Ray(Vector ori, Vector dir){
    origin = ori;
    direction = dir;
}

#endif
