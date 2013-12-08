//
//  main.cpp
//  CS3388_Assignment4-raytracer
//
//  This file contains the main code for the raytracer program, including the raytracing algorithm.
//  The program was created with reference to class notes (and some provided code), as well as other references: http://bit.ly/J13azP and http://bit.ly/18s9aKX.
//
//  Created by Jake on 2013-12-06.
//

// Include external libraries
#include <stdio.h>
#include <X11/Xlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <cmath>
#include <vector>
#include <string>

// Include internal libraries
#include "RGB.h"
#include "Vector.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"
#include "Plane.h"

// Define window defaults
#define WINDOW_X 10
#define WINDOW_Y 10
#define WINDOW_HEIGHT 640
#define WINDOW_WIDTH 640

using namespace std;

// GLOBALS
// Scene Settings
int CAM_X = 1;
int CAM_Y = 1;
int CAM_Z  = -5;

int LIGHT_X = 3;
int LIGHT_Y = -1;
int LIGHT_Z = -4;
double SPECULAR_FACTOR = 10;
double AMBIENCE = 0.25;
double SHADOW_FACTOR = 1;

// List of all objects
vector<Object*>* objects;

// Global vectors
// Define unit vectors
Vector i_vec(1,0,0);
Vector j_vec(0,1,0);
Vector k_vec(0,0,1);
Vector origin(0,0,0);

// Define some basic colours
Colour white(1.0, 1.0, 1.0, 0.0);
Colour black(0.0, 0.0, 0.0, 0.0);
Colour reflective_green(0.1, 0.75, 0.0, 1.0);
Colour reflective_red(1.0, 0.0, 0.0, 1.0);
Colour reflective_blue(0.0, 0.2, 0.75, 1.0);
Colour matte_white(1.0, 1.0, 1.0, 0.4);

// X11 Variables
Display *display;
Window window;
XEvent event;
int s;

// Function to initialize the X11 environment
// Input: display (Display*); window (Window*); s (int*)
// Output: none
Display *InitX(Display *display, Window *window, int *s) {
    display = XOpenDisplay(NULL);
    if(display == NULL) {
        printf("Cannot open display\n");
        exit(1);
    }
    *s = DefaultScreen(display);
    *window = XCreateSimpleWindow(display, RootWindow(display, *s), WINDOW_X, WINDOW_Y, WINDOW_WIDTH, WINDOW_HEIGHT, 1, BlackPixel(display, *s), WhitePixel(display, *s));
    Atom delWindow = XInternAtom(display, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(display, *window, &delWindow, 1);
    XSelectInput(display, *window, ExposureMask | KeyPressMask);
    XMapWindow(display, *window);
    return(display);
}

// Function to set the current colour to use
// Input: d (Display*); gc (GC*); r,g,b (unsigned int)
// Output: none
void SetCurrentColorX(Display *d, GC *gc, unsigned int r, unsigned int g, unsigned int b) {
    XSetForeground(d, *gc, r << 16 | g << 8 | b);
}

// Function to set the pixel to the current colour being used
// Input: d (Display*); w (Window); s,i,j (int)
// Output: none
void SetPixelX(Display *d, Window w, int s, int i, int j) {
    XDrawPoint(d, w, DefaultGC(d, s), i, j);
}

// Function to destroy and close the X11 window
// Input: d (Display*); w (Window)
// Output: none
void QuitX(Display *d, Window w) {
    XDestroyWindow(d,w);
    XCloseDisplay(d);
}

// Function to calculate the scalar used to generate the projected value of x onto the viewing surface
// Input: x (int)
// Output: the projected value of x (double)
double x_projection_factor(int x){
    return (x + 0.5)/WINDOW_WIDTH;
    
}

// Function to calculate the scalar used to generate the projected value of y onto the viewing surface
// Input: y (int)
// Output: the projected value of y (double)
double y_projection_factor(int y){
    return ((WINDOW_HEIGHT - y) + 0.5)/WINDOW_HEIGHT;
}

// Function to gather any required data from the user
// Input: none
// Output: whether or not the program gathered input or not (Returns true if input was gathered) (bool)
bool gatherInput(){
    string input = "";
    while (!(input.compare("y")==0) && !(input.compare("n")==0)){
        cout << "Use default settings? (y/n): ";
        cin >> input;
    }
    // Gather input if the user desires
    if (input == "y"){
        return false;
    }
    else{
        // Gather camera info
        cout << "Collecting data for the camera.\nEnter it's x coordinate: ";
        cin >> input;
        CAM_X = stoi(input);
        cout << "Enter it's y coordinate: ";
        cin >> input;
        CAM_Y = stoi(input);
        cout << "Enter it's z coordinate: ";
        cin >> input;
        CAM_Z = stoi(input);
        // Gather light info
        cout << "Collecting data for the light.\nEnter it's x coordinate: ";
        cin >> input;
        LIGHT_X = stoi(input);
        cout << "Enter it's y coordinate: ";
        cin >> input;
        LIGHT_Y = stoi(input);
        cout << "Enter it's z coordinate: ";
        cin >> input;
        LIGHT_Z = stoi(input);
        // Gather object info
        while (!(input.compare("n")==0)){
            Object *obj;
            double r,g,b,reflectiveness;
            cout << "Define objects.\nSphere ('s') or Plane('p')? ";
            cin >> input;
            // Sphere
            if (input.compare("s")==0){
                double radius,x,y,z;
                cout << "Enter it's radius: ";
                cin >> input; radius = stod(input);
                cout << "Enter its centre X position: ";
                cin >> input; x = stod(input);
                cout << "Enter its centre Y position: ";
                cin >> input; y = stod(input);
                cout << "Enter its centre Z position: ";
                cin >> input; z = stod(input);
                Vector pos(x,y,z);
                
                // Create the new object
                obj = new Sphere(pos,radius,Colour());
            }
            // Plane
            else if (input.compare("p")==0){
                double size,x,y,z;
                // Position (center of plane)
                cout << "Enter its centre X position: ";
                cin >> input; x = stod(input);
                cout << "Enter its centre Y position: ";
                cin >> input; y = stod(input);
                cout << "Enter its centre Z position: ";
                cin >> input; z = stod(input);
                Vector pos(x,y,z);
                
                // Vector a in the plane
                cout << "Define a vector 'a' in the plane.\n";
                cout << "Enter a's X position: ";
                cin >> input; x = stod(input);
                cout << "Enter a's Y position: ";
                cin >> input; y = stod(input);
                cout << "Enter a's Z position: ";
                cin >> input; z = stod(input);
                Vector a(x,y,z);
                
                // Vector b in the plane
                cout << "Define a vector 'b' in the plane.\n";
                cout << "Enter b's X position: ";
                cin >> input; x = stod(input);
                cout << "Enter b's Y position: ";
                cin >> input; y = stod(input);
                cout << "Enter b's Z position: ";
                cin >> input; z = stod(input);
                Vector b(x,y,z);
                
                // How far should it span?
                cout << "How far should the plane span? ";
                cin >> input;
                size = stod(input);
                
                obj = new Plane(pos, a, b, Colour(), size);
            } else continue;
            // Get its colour
            cout << "Enter it's red value (0 to 1): ";
            cin >> input; r = stod(input);
            cout << "Enter it's green value (0 to 1): ";
            cin >> input; g = stod(input);
            cout << "Enter it's blue value (0 to 1): ";
            cin >> input; b = stod(input);
            cout << "Enter it's reflectiveness coefficient (0 to 1): ";
            cin >> input; reflectiveness = stod(input);
            Colour colour = Colour(r,g,b,reflectiveness);
            
            // Add the object to the list
            obj->colour = colour;
            objects->push_back(obj);
            
            // Ask the user if they want to continue
            cout << "Continue to define more shapes (y/n)? ";
            cin >> input;
        }
        return true;
    }
    
}

// The main function of the program
// Input: none
// Output: exit code (int)
int main() {
    objects = new vector<Object*>();
    
    // Initialize the pixels
    vector<vector<RGB>> pixels(WINDOW_WIDTH);
    for (int i=0; i<pixels.size(); i++){
        pixels[i] = vector<RGB>(WINDOW_HEIGHT);
    }
    
    if (!gatherInput()){
        // DEFINE A DEFAULT SCENE IF NO USER INPUT WAS PROVIDED
        // Define a sphere
        double sphere1_radius = 0.2;
        Vector sphere1_position = origin.plus(j_vec.scale(0.3)).plus(i_vec.scale(0.2)).plus(k_vec.scale(-0.1));
        Colour sphere1_colour = reflective_green;
        Sphere sphere1(sphere1_position, sphere1_radius, sphere1_colour);
        
        double sphere2_radius = 0.3;
        Vector sphere2_position = origin.plus(i_vec.scale(-0.2));
        Colour sphere2_colour = reflective_blue;
        Sphere sphere2(sphere2_position, sphere2_radius, sphere2_colour);
        
        double sphere3_radius = 0.2;
        Vector sphere3_position = origin.plus(j_vec.scale(-0.5)).plus(k_vec);
        Sphere sphere3(sphere3_position, sphere3_radius, matte_white);
        
        // Define a plane
        // Default = x/y plane when z=-1
        Plane plane(Vector(0,0,-1), Vector(1,1,0), Vector(0,1,-0.1), reflective_red, 2.2);
        
        // Keep track of all objects
        objects->push_back(&sphere1);
        objects->push_back(&sphere2);
        objects->push_back(&sphere3);
        objects->push_back(&plane);
    }
    
    // Define the camera
    Vector camera_location(CAM_X, CAM_Y, CAM_Z);                        // Place the camera at CAM_X,CAM_Y,CAM_Z
    Vector camera_gaze(camera_location.scale(-1));                      // The camera is gazing at the origin
    Vector camera_right(j_vec.cross(camera_gaze).normalize());          // The camera's right unit vector is = j x gaze
    Vector camera_down(camera_right.cross(camera_gaze).normalize());    // The camera's down unit vector is = right x gaze
    Camera cam(camera_location,camera_gaze,camera_right,camera_down);
    
    // Define a light source
    Vector light_location(LIGHT_X, LIGHT_Y, LIGHT_Z);
    Light light(light_location, white);
    
    // Display window and begin raytracing algorithm
    display = InitX(display, &window, &s);
    while (1) {
        XNextEvent(display, &event);
        if (event.type == Expose) {
            // Trace top to bottom, and slowly move right
            for (int x = 0; x < WINDOW_WIDTH; x++) {
                for (int y = 0; y < WINDOW_HEIGHT; y++) {
                    // Handle the viewing plane
                    double x_factor = x_projection_factor(x), y_factor = y_projection_factor(y);
                    
                    // Make a ray for this pixel (starts at camera, direction is the gaze + variance in the x and y)
                    Vector ray_origin = cam.position;
                    Vector ray_direction = cam.gaze.plus(cam.right.scale(x_factor - 0.5).plus(cam.down.scale(y_factor - 0.5))).normalize();
                    Ray ray(ray_origin, ray_direction);
                    
                    // Find the intersection distance for each object
                    Object *closest = NULL;
                    double smallest_distance = -1;
                    for (int i = 0; i < objects->size(); i++){
                        double distance = (*objects)[i]->findIntersectionDistance(ray);
                        if (distance < 0)
                            continue;
                        else if (closest == NULL || distance < smallest_distance){
                            smallest_distance = distance;
                            closest = (*objects)[i];
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
                        for (int i = 0; i < objects->size(); i++){
                            if ((*objects)[i]->findIntersectionDistance(shadow_feeler_ray) >= 0){
                                shadow = true;
                                break;
                            }
                        }
                        
                        // Ambient light
                        Colour resulting_colour = closest->colour.applyScalar(AMBIENCE);
                        
                        // Calculate required vectors
                        // Calculate the colour at the point
                        // Vector "s" - the vector to the light source
                        Vector s = light.position.minus(intersection_point).normalize();
                        // Vector "v" - the vector back to the center of projection
                        Vector v = ray_direction.scale(-1).normalize();
                        // Vector "n" - the object's normal
                        Vector n = closest->getNormalAtPoint(intersection_point).normalize();
                        // Vector "r" (direction of specular reflection) = v + (ray_direction + n*(n.v))*2
                        Vector r = v.plus(ray_direction.plus(n.scale(n.dot(v))).scale(2)).normalize();
                    
                        if (!shadow){
                            // Diffusive
                            double diffusive_factor = s.dot(n);
                            if (diffusive_factor > 0) {
                                resulting_colour = resulting_colour.plus(light.colour.applyScalar(diffusive_factor*closest->colour.reflectiveness)).correct();
                            }
                            
                            // Specular
                            double specular_factor = r.dot(s);
                            if (specular_factor > 0) {
                                specular_factor = pow(specular_factor, SPECULAR_FACTOR);
                                resulting_colour = resulting_colour.plus(light.colour.applyScalar(specular_factor*closest->colour.reflectiveness)).correct();
                            }
                            pixels[x][y].r = resulting_colour.r*255;
                            pixels[x][y].g = resulting_colour.g*255;
                            pixels[x][y].b = resulting_colour.b*255;
                        }
                        else{
                            pixels[x][y].r = resulting_colour.r*255/SHADOW_FACTOR;
                            pixels[x][y].g = resulting_colour.g*255/SHADOW_FACTOR;
                            pixels[x][y].b = resulting_colour.b*255/SHADOW_FACTOR;
                        }
                        
                    }
                    
                    // Draw the pixel
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
    // Clean up
    delete objects;
}

