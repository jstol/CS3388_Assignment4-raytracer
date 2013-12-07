//
//  Camera.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef CS3388_Assignment4_raytracer_Camera_h
#define CS3388_Assignment4_raytracer_Camera_h

#include "Vector.h"

class Camera {
public:
    Vector position, gaze, right, down;
    Camera();
    Camera(Vector, Vector, Vector, Vector);
};

Camera::Camera (){
    // By default it is at 0,0,0 and is looking along the x axis
    position = Vector(0,0,0);
    gaze = Vector(1,0,0);
    right = Vector(0,-1,0);
    down = Vector(0,0,-1);
}

Camera::Camera(Vector e, Vector g, Vector r, Vector d){
    position = e;
    gaze = g;
    right = r;
    down = d;
}

#endif
