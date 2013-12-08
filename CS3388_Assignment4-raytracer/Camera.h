//
//  Camera.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold data related to a camera object.
//
//  Created by Jake on 2013-12-06.
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

// Default constructor
// Input: none
// Output: N/A
Camera::Camera (){
    // By default it is at 0,0,0 and is looking along the x axis
    position = Vector(0,0,0);
    gaze = Vector(1,0,0);
    right = Vector(0,-1,0);
    down = Vector(0,0,-1);
}

// Constructor which allows for the camera's vectors to be initialized
// Input: e,g,r,d (Vector)
// Output: N/A
Camera::Camera(Vector e, Vector g, Vector r, Vector d){
    position = e;
    gaze = g;
    right = r;
    down = d;
}

#endif
