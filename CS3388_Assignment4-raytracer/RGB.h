//
//  RGB.h
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
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

RGB::RGB(){
    r = 0;
    g = 0;
    b = 0;
}

RGB::RGB(double r,  double g,double b){
    this->r = r;
    this->g = g;
    this->b = b;
}

#endif
