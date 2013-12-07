//
//  Ray.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef CS3388_Assignment4_raytracer_Ray_h
#define CS3388_Assignment4_raytracer_Ray_h

class Ray {
public:
    Vector origin, direction;
    Ray();
    Ray(Vector, Vector);
};

Ray::Ray (){
    // Default origin is 0,0,0; Default direction is in the X-Direction
    origin = Vector(0,0,0);
    direction = Vector(1,0,0);
}

Ray::Ray(Vector ori, Vector dir){
    origin = ori;
    direction = dir;
}

#endif
