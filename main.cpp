//
//  main.cpp
//  corona
//
//  Created by Gohar Kunjiyan on 1/28/21.
//  Copyright © 2021 Gohar Kunjiyan. All rights reserved.
//

#include <iostream>
//this file is used to draw function with openGL, remove from the comment in case of drawing
#include "glutWindow.h"
#include "util_functions.h"

//width and height of the opengl window
#define w 600
#define h 400


#include "simulator.h"

double eps = 0.075;
//iteration count
const int N = 10;

//index of I_k to be drawn
const int N_D = 5;

double x_m_treshold = 20;




//field x to get values of I_k(x_j)
field x(0, 30, 0.5);
//field t defined to use it in intergral calculation
field t(0, 30, 0.5);
//sequence of I_k functions
i_sequence seq(x, N);


//this section is for drawing using OpenGL, if you dont have issues with that library -> remove from the comment section
void display() {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f); // Set background color to black and opaque
    glClear(GL_COLOR_BUFFER_BIT);         // Clear the color buffer (background)
    
    double x_m = (x.b - x.a) < x_m_treshold ? 1 : 10 * w;
 
    
    glBegin(GL_LINE_STRIP);// to draw a smooth line
    glColor3d(1.0, 0.0, 0.0); //rgb color
    for(int i = 0; i < x.points.size(); ++i){
        double xpos = x.a+(x.b-x.a)*x.points[i]/(x_m);
        double ypos = seq.fi_(N_D)->get_point(x.points[i]);
        glVertex2d(xpos, ypos);
        
    }
    glEnd();
    
    glFlush();  // Render now
}

//drawing class
class GLWW: public GlutWindow {
public:
    GLWW(int argc, char** argv): GlutWindow(argc, argv, "test", w, h){}
    void onStart() override{}
    void onDraw() override{
        display();
    }
    void onQuit() override{}
};





int main(int argc, char ** argv) {
    
    
    //initialize simulator, which calculates i_sequence
    simulator algorithm_runner(x, t , seq);
    
    //i_sequence calculation
    algorithm_runner.fill_sequence();
    
   
    for (int j = 0; j <= N_D; ++j) {
      std::cout << "I_" << j << " X_MAX: " << algorithm_runner.sequence.fi_(j)->max_x << "  Y_MAX: " << algorithm_runner.sequence.fi_(j)->max_y << std::endl;
    for (int i = 0; i < x.points.size(); ++i) {
        std::cout << x.points[i] << ": " << algorithm_runner.sequence.fi_(j)->get_point(x.points[i]) << "  "
        << std::endl;
    }
        std::cout << std::endl;
        
    }
    
    
    seq.i_k = algorithm_runner.sequence.i_k;
    
    //this section is to draw the function using OpenGL
    /*GLWW r(argc, argv);
    r.start();*/
    return 0;
    
}
