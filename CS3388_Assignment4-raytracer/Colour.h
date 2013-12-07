//
//  Colour.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
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
};

Colour::Colour () {
	r = 1.0;
	g = 1.0;
	b = 1.0;
}

Colour::Colour (double r, double g, double b, double ref) {
	this->r = r;
	this->g = g;
	this->b = b;
	this->reflectiveness = ref;
}

double Colour::getBrightness(){
    return (r+g+b)/3;
}

Colour Colour::plus(Colour c){
    return Colour(r+c.r,g+c.g,b+c.b,reflectiveness+c.reflectiveness);
}

Colour Colour::times(Colour c){
    return Colour(r*c.r,g*c.g,b*c.b,reflectiveness*c.reflectiveness);
}

Colour Colour::getAverage(Colour c){
    return Colour((r+c.r)/2,(g+c.g)/2,(b+c.b)/2,(reflectiveness+c.reflectiveness)/2);
}

Colour Colour::applyScalar(double k){
    return Colour(r*k,g*k,b*k,reflectiveness*k);
}

#endif
