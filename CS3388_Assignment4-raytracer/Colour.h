//
//  Colour.h
//  CS3388_Assignment4-raytracer
//
//  This class was created to hold data related to colours, as well as any methods it might require.
//
//  Created by Jake on 2013-12-06.
//

#ifndef CS3388_Assignment4_raytracer_Colour_h
#define CS3388_Assignment4_raytracer_Colour_h

class Colour{
public:
    double r,g,b,reflectiveness;
    
    Colour();
    Colour(double,double,double,double);
    
    // Methods
    double getBrightness();
    Colour plus(Colour c);
    Colour times(Colour c);
    Colour getAverage(Colour c);
    Colour applyScalar(double k);
    Colour correct();
};

// Default constructor
// Input: none
// Output: N/A
Colour::Colour () {
	r = 1.0;
	g = 1.0;
	b = 1.0;
}

// Constructor to allow for the r,g,b and reflectiveness coefficient to be initialized
// Input: r,g,b, ref (double)
// Output: N/A
Colour::Colour (double r, double g, double b, double ref) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->reflectiveness = ref;
}

// Function to return the "brightness" of the colour
// Input: none
// Output: brightness (double)
double Colour::getBrightness(){
    return (r+g+b)/3;
}

// Function to "add" a colour to another
// Input: c (Colour)
// Output: the result (Colour)
Colour Colour::plus(Colour c){
    return Colour(r+c.r,g+c.g,b+c.b,reflectiveness+c.reflectiveness);
}

// Function to multiply the colour by a scalar
// Input: k (double)
// Output: the result (Colour)
Colour Colour::applyScalar(double k){
    return Colour(r*k,g*k,b*k,reflectiveness*k);
}

// Function to "correct" a colour so that it's r,g,b values aren't outside of the range [0..1]
// Input: none
// Output: the resulting colour (Colour)
Colour Colour::correct(){
    // Fix the boundaries of the colour
    if (r < 0) r = 0;
    else if (r > 1) r = 1;
    if (g < 0) g = 0;
    else if (g > 1) g = 1;
    if (b < 0) b = 0;
    else if (b > 1) b = 1;
    
    return *this;
}

#endif
