//
//  Light.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold data related to light objects.
//
//  Created by Jake on 2013-12-06.
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

// Default constructor
// Input: none
// Output: N/A
Light::Light() {
    // Default position at origin; default colour white
	position = Vector(0,0,0);
	colour = Colour(1,1,1,0);
}

// Constructor that allows for the light's position and colour to be initialized
// Input: p (Vector), c (Colour)
// Output: N/A
Light::Light(Vector p, Colour c) {
	position = p;
	colour = c;
}

#endif
