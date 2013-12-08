//
//  RGB.h
//  CS3388_Assignment4-raytracer
//
//  This is a utility class for dealing with RGB colour values.
//
//  Created by Jake on 2013-12-06.
//

#ifndef CS3388_Assignment4_raytracer_RGB_h
#define CS3388_Assignment4_raytracer_RGB_h

class RGB{
public:
    double r;
    double g;
    double b;
    
    RGB();
    RGB(double,double,double);
};

// Default constructor
// Input: none
// Output: N/A
RGB::RGB(){
    r = 0;
    g = 0;
    b = 0;
}

// Constructor that takes initial RGB values
// Input: r,g,b (double)
// Output: N/A
RGB::RGB(double r,  double g, double b){
    this->r = r;
    this->g = g;
    this->b = b;
}

#endif
