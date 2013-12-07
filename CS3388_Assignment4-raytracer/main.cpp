//
//  main.cpp
//  CS3388_Assignment4-raytracer
//
//  Created by Jake on 2013-12-06.
//  Copyright (c) 2013 Jake. All rights reserved.
//

#include <stdio.h>

#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <limits>
#include <vector>
#include <string>

// Include private libraries
#include "matrix.h"
#include "RGB.h"
#include "Vector.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

#define POS_X 10
#define POS_Y 10

#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640
#define ASPECT_RATIO 1.0

#define CAM_X 1
#define CAM_Y 4
#define CAM_Z -4.5

#define LIGHT_X 3
#define LIGHT_Y 10
#define LIGHT_Z -4

#define AMBIENCE 0.2

using namespace std;

Display *InitX(Display *display, Window *window, int *s) {
    
    display = XOpenDisplay(NULL);
    if(display == NULL) {
        printf("Cannot open display\n");
        exit(1);
    }
    *s = DefaultScreen(display);
    *window = XCreateSimpleWindow(display, RootWindow(display, *s), POS_X, POS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, 1, BlackPixel(display, *s), WhitePixel(display, *s));
    Atom delWindow = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, *window, &delWindow, 1);
    XSelectInput(display, *window, ExposureMask | KeyPressMask);
    XMapWindow(display, *window);
    return(display);
}


void SetCurrentColorX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
    XSetForeground(d, *gc, r << 16 | g << 8 | b);
}


void SetPixelX(Display *d, Window w, int s, int i, int j) {
    XDrawPoint(d, w, DefaultGC(d, s), i, j);
}


void QuitX(Display *d, Window w) {
    XDestroyWindow(d,w);
    XCloseDisplay(d);
}

double x_variance(int x){
    return (x + 0.5)/WINDOW_WIDTH;
    
}

double y_variance(int y){
    return ((WINDOW_HEIGHT - y) + 0.5)/WINDOW_HEIGHT;
}

int main() {
    // Matrix stuff
    dmatrix_t A;
    
    dmat_alloc(&A,3,3);
    
    A.m[1][1] = 1.0; A.m[1][2] = 2.0; A.m[1][3] = 0.0;
    A.m[2][1] = -1.0; A.m[2][2] = 1.0; A.m[2][3] = 1.0;
    A.m[3][1] = 1.0; A.m[3][2] = 2.0; A.m[3][3] = 3.0;
    
    printf("\n The matrix is:\n");
    write_dmatrix(&A);
    
    printf("\n Its inverse matrix is:\n");
    write_dmatrix(dmat_inverse(&A));
    
    printf("\n The matrix multiplied with its inverse yields the identity matrix:\n");
    write_dmatrix(dmat_mult(&A,dmat_inverse(&A)));
    
    // X11 Stuff
    Display *display;
    Window window;
    XEvent event;
    int s;
    
    // Define a matrix to hold all pixel values on the screen
    vector<vector<RGB>> pixels(WINDOW_WIDTH);
    for (int i=0; i<pixels.size(); i++){
        pixels[i] = vector<RGB>(WINDOW_HEIGHT);
    }
    
    // Define unit vectors
    Vector i_vec(1,0,0);
    Vector j_vec(0,1,0);
    Vector k_vec(0,0,1);
    Vector origin(0,0,0);
    
    // Define the camera
    Vector camera_location(CAM_X, CAM_Y, CAM_Z);                        // Place the camera at CAM_X,CAM_Y,CAM_Z
    Vector camera_gaze(camera_location.scale(-1));                      // The camera is gazing at the origin
    Vector camera_right(j_vec.cross(camera_gaze).normalize());          // The camera's right unit vector is = j x gaze
    Vector camera_down(camera_right.cross(camera_gaze).normalize());    // The camera's down unit vector is = right x gaze
    Camera cam(camera_location,camera_gaze,camera_right,camera_down);
    
    // Define colours
    Colour white(1.0, 1.0, 1.0, 0.0);
    Colour black(0.0, 0.0, 0.0, 0.0);
    Colour reflective_green(0.0, 1.0, 0.0, 0.5);
    Colour reflective_red(1.0, 0.0, 0.0, 0.5);
    Colour reflective_blue(0.0, 0.0, 1.0, 0.5);
    
    // Define a light source
    Vector light_location(LIGHT_X, LIGHT_Y, LIGHT_Z);
    Light light(light_location, white);

    // Define a sphere
    double sphere1_radius = 0.2;
    Vector sphere1_position = origin.plus(j_vec.scale(0.2));
    Colour sphere1_colour = reflective_green;
    Sphere sphere1(sphere1_position, sphere1_radius, sphere1_colour);

    double sphere2_radius = 0.3;
    Vector sphere2_position = origin.plus(i_vec.scale(-0.2));
    Colour sphere2_colour = reflective_blue;
    Sphere sphere2(sphere2_position, sphere2_radius, sphere2_colour);

    double sphere3_radius = 0.2;
    Vector sphere3_position = origin.plus(j_vec.scale(-0.5)).plus(k_vec.scale(0.2));
    Sphere sphere3(sphere3_position, sphere3_radius, white);
    
    // Define a plane
    // Default = x/y plane when z=-1
    Plane plane(Vector(0,0,-1), Vector(1,0,0), Vector(0.3,0.3,0.3), reflective_red, 7);
    
    // Keep track of all objects
    // TODO Is this done wrong?
    vector<Object*> objects;
    objects.push_back(&sphere1);
    objects.push_back(&sphere2);
    objects.push_back(&sphere3);
    objects.push_back((Object*)&plane);
    
    display = InitX(display, &window, &s);
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Trace top to bottom, and slowly move right
            for (int x = 0; x < WINDOW_WIDTH; x++) {
                for (int y = 0; y < WINDOW_HEIGHT; y++) {
                    // Handle the viewing plane
                    double x_factor = x_variance(x), y_factor = y_variance(y);
                    
                    // Make a ray for this pixel (starts at camera, direction is the gaze + variance in the x and y
                    Vector ray_origin = cam.position;
                    Vector ray_direction = cam.gaze.plus(cam.right.scale(x_factor - 0.5).plus(cam.down.scale(y_factor - 0.5))).normalize();
                    Ray ray (ray_origin, ray_direction);
                    
                    // Find the intersection distance for each object
                    //vector<double> intersection;
                    Object *closest = NULL;
                    double smallest_distance = -1;
                    for (int i = 0; i < objects.size(); i++){
                        double distance = objects[i]->findIntersectionDistance(ray);
                        if (distance < 0)
                            continue;
                        else if (closest == NULL || distance < smallest_distance){
                            smallest_distance = distance;
                            closest = objects[i];
                        }
                    }
                        
                    // Set the pixel colour based on the object. If no object was closest, set it to black
                    if (closest == NULL){
                        pixels[x][y].r = pixels[x][y].g = pixels[x][y].b = 0;
                    } else {
                        // Find intersection point
                        Vector intersection_point = ray.origin.plus(ray.direction.scale(smallest_distance));
                        bool shadow = false;
                        
                        // Check if there's a shadow
                        Ray shadow_feeler_ray (intersection_point, light.position.minus(intersection_point).normalize());
                        for (int i = 0; i < objects.size(); i++){
                            if (objects[i]->findIntersectionDistance(shadow_feeler_ray) >= 0){
                                shadow = true;
                                break;
                            }
                        }
                        if (shadow){
                            pixels[x][y].r = (closest->colour.r*255)/2;
                            pixels[x][y].g = (closest->colour.g*255)/2;
                            pixels[x][y].b = (closest->colour.b*255)/2;
                        }
                        else{
                            pixels[x][y].r = closest->colour.r*255;
                            pixels[x][y].g = closest->colour.g*255;
                            pixels[x][y].b = closest->colour.b*255;
                            
                        }
                    }
                    
                    // Draw the pixel
                    //r = x; g = y; b = y;
                    SetCurrentColorX(display, &(DefaultGC(display, s)), pixels[x][y].r, pixels[x][y].g, pixels[x][y].b);
                    SetPixelX(display, window, s, x, y);
                }
            }
        }
        if(event.type == KeyPress)
            break;
        if(event.type == ClientMessage)
            break;
    }
    QuitX(display,window);
}

