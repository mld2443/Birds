///////////////////////////////////////////////
//  main.cpp                                 //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/12/15.  //
///////////////////////////////////////////////

// Stops clang warnings about using OpenGL and GLUT
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

//////////////
// Includes //
//////////////

#include <GLUT/GLUT.h>
#include <OpenGL/gl.h>

#include "terrarium.h"


/////////////
// Globals //
/////////////

// timing information
unsigned int steps_per_frame;
double fps, timestep;
bool play;

// camera info
GLfloat c_ratio;
float movespeed;
float camPhi, camTheta;
float3 eyePos, lookDir;
bool follow;
unsigned int follow_flock;

// scene data
int window;
terrarium t;


/// Designated OpenGL update function. Called to draw every frame.
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();
    
    if (follow) {
        lookDir = t.camera_dir(follow_flock).rotateX(camPhi).rotateY(camTheta);;
        eyePos = t.camera_pos(follow_flock) - (lookDir * 200);
    }
    
    gluLookAt(eyePos.x, eyePos.y, eyePos.z, (eyePos+lookDir).x, (eyePos+lookDir).y, (eyePos+lookDir).z, 0, 1, 0);
    
    t.draw();
    
    glPopMatrix();
    glutSwapBuffers();
}

/// Simulation initialization
void init() {
    // Enable Z-buffering, backface culling, and lighting
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, c_ratio, 1, 6000);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // simulation timing
    // feel free to change these, more steps/frame means more accurate simulation
    steps_per_frame = 1;
    fps = 60.0; // More of a suggestion
    timestep = 1.0/(fps * steps_per_frame);
    play = true;
    
    // looking and movement
    movespeed = 10.0;
    follow_flock = 0;
    follow = true;
    
    t = terrarium();
}

/// Designated OpenGL window resize function. Called every time the window is resized
void resizeFunc(GLint newWidth, GLint newHeight) {
    c_ratio = (GLfloat)newWidth/(GLfloat)newHeight;
    init();
    glutPostRedisplay();
}


/// Primary Simulation happens here. A callback is set up to be called at every desired frame.
/// If the frame calculation pipeline is faster than desired FPS, the callback caps the framerate.
void newFrame(const int id) {
    glutTimerFunc(1000.0/fps, newFrame, 1);
    
    if (play) {
        unsigned int step = 0;
        
        while (step < steps_per_frame) {
            t.step(timestep);
            step++;
        }
        
        // Primary frame refresh
        glutPostRedisplay();
    }
}

/// Designated GLUT keyboard input callback.
void key(const unsigned char c, const int x, const int y) {
    //space - play/pause
    //c - toggle free camera
    //1 - toggle which flock to follow, (make sure not to press this unless there's at least 2 flocks)
    //wasd - move camera in free camera
    //arrows - look aroud
    //esc - exit
    switch (c) {
        case ' ':
            play = !play;
            break;
        case 27: // escape key
            glutDestroyWindow(window);
            exit(0);
            break;
            
        case 'c':
            follow = !follow;
            if (follow) {
                camTheta = 315;
                camPhi = -30;
            } else {
                camTheta = 315;
                camPhi = -30;
                lookDir = float3(1, 0, 0).rotateZ(camPhi).rotateY(camTheta);
                eyePos = float3(4500.f, 500.f, 4500.f);
            }
            glutPostRedisplay();
            break;
            
        case '1':
            follow_flock = !follow_flock;
            glutPostRedisplay();
            break;
            
        case 'w':
            eyePos += lookDir * movespeed;
            glutPostRedisplay();
            break;
        case 'a':
            eyePos -= lookDir.cross(float3(0,1,0)).normalize() * movespeed;
            glutPostRedisplay();
            break;
        case 's':
            eyePos -= lookDir * movespeed;
            glutPostRedisplay();
            break;
        case 'd':
            eyePos += lookDir.cross(float3(0,1,0)).normalize() * movespeed;
            glutPostRedisplay();
            break;
            
        case 'W':
            eyePos += lookDir * 2.0 * movespeed;
            glutPostRedisplay();
            break;
        case 'A':
            eyePos -= lookDir.cross(float3(0,1,0)).normalize() * 2.0 * movespeed;
            glutPostRedisplay();
            break;
        case 'S':
            eyePos -= lookDir * 2.0 * movespeed;
            glutPostRedisplay();
            break;
        case 'D':
            eyePos += lookDir.cross(float3(0,1,0)).normalize() * 2.0 * movespeed;
            glutPostRedisplay();
            break;
            
        default:
            break;
    }
}

/// Designated GLUT special key callback.
void specialKey(const int c, const int x, const int y){
    switch (c) {
        case GLUT_KEY_UP:
            if (camPhi + 5 < 90) {
                camPhi += 5;
                if (!follow)
                    lookDir = float3(1,0,0).rotateZ(camPhi).rotateY(camTheta);
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_DOWN:
            if (camPhi - 5 > -90) {
                camPhi -= 5;
                if (!follow)
                    lookDir = float3(1,0,0).rotateZ(camPhi).rotateY(camTheta);
                glutPostRedisplay();
            }
            break;
        case GLUT_KEY_LEFT:
            camTheta -= 5;
            if (camTheta >= 360)
                camTheta -= 360;
            if (!follow)
                lookDir = float3(1,0,0).rotateZ(camPhi).rotateY(camTheta);
            glutPostRedisplay();
            break;
        case GLUT_KEY_RIGHT:
            camTheta += 5;
            if (camTheta < 0)
                camTheta += 360;
            if (!follow)
                lookDir = float3(1,0,0).rotateZ(camPhi).rotateY(camTheta);
            glutPostRedisplay();
            break;
            
        default:
            break;
    }
}


/// Main function, initializes the GLUT values, calls the initializer, and calls the main loop.
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
    glutInitWindowPosition(0, 0);
    window = glutCreateWindow("Birds of paradise");
    glutDisplayFunc(display);
    glutFullScreen();
    glutKeyboardFunc(key);
    glutSpecialFunc(specialKey);
    glutTimerFunc(1000.0/fps, newFrame, 0);
    glutReshapeFunc(resizeFunc);
    
    init();
    
    glutMainLoop();
    return 0;
}
