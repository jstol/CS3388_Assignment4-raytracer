//
//  Light.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#ifndef CS3388_Assignment4_raytracer_Light_h
#define CS3388_Assignment4_raytracer_Light_h

#include "Vector.h"
#include "Colour.h"

class Light{
public:
	Vector position;
	Colour colour;
    
	Light();
	Light(Vector, Colour);
};

Light::Light() {
    // Default position at origin; default colour white
	position = Vector(0,0,0);
	colour = Colour(1,1,1,0);
}

Light::Light(Vector p, Colour c) {
	position = p;
	colour = c;
}

#endif
