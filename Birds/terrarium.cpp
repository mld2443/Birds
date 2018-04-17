///////////////////////////////////////////////
//  terrarium.cpp                            //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/12/15.  //
///////////////////////////////////////////////

// Removes warnings for using OpenGL and GLUT
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "terrarium.h"

/// Sets up the sun-like lighting.
void terrarium::draw_lights() const {
    // Install lights
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0color);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1color);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1color);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1color);
}

/// Draws a contrasting grass-like ground with a small stream down the middle
void terrarium::draw_ground() const {
    glMaterialfv(GL_FRONT, GL_AMBIENT, gnd_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gnd_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gnd_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, gnd_shininess);
    
    glBegin(GL_QUADS); {
        glNormal3f(0.f, 1.f, 0.f);
        glVertex3f(boxxh, boxyl, boxzh);
        glVertex3f(boxxh, boxyl, rdepth + rwidth);
        glVertex3f(boxxl, boxyl, ldepth + lwidth);
        glVertex3f(boxxl, boxyl, boxzh);
    } glEnd();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, water_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, water_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, water_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, water_shininess);
    
    glBegin(GL_QUADS); {
        glNormal3f(0.f, 1.f, 0.f);
        glVertex3f(boxxl, boxyl, ldepth + lwidth);
        glVertex3f(boxxh, boxyl, rdepth + rwidth);
        glVertex3f(boxxh, boxyl, rdepth - rwidth);
        glVertex3f(boxxl, boxyl, ldepth - lwidth);
    } glEnd();
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, gnd_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gnd_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gnd_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, gnd_shininess);
    
    glBegin(GL_QUADS); {
        glNormal3f(0.f, 1.f, 0.f);
        glVertex3f(boxxl, boxyl, boxzl);
        glVertex3f(boxxl, boxyl, ldepth - lwidth);
        glVertex3f(boxxh, boxyl, rdepth - rwidth);
        glVertex3f(boxxh, boxyl, boxzl);
    } glEnd();
}

/// Draws a rock, important as a landmark to keep track of scale
void terrarium::draw_rock(const int x, const int y, const int z, const float h, const int w, const int l, const int r) const {
    // Define rock colors
    glMaterialfv(GL_FRONT, GL_AMBIENT, rock_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rock_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, rock_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, rock_shininess);
    
    // Intermediate values
    float topx = w / 3.f, topz = l / 3.f;
    float halfx = w / 2.f, halfz = l / 2.f;
    float p2z = (2.f * l / 3.f) - halfz, p3x = halfx - (2.f * w / 3.f);
    float p7z = (4.f * l / 9.f) - topz, p8x = topx - (4.f * w / 9.f);
    
    glPushMatrix(); {
        glTranslatef(x, y, z);
        glRotatef(r, 0.f, 1.f, 0.f);
        
        // Define the rock points
        float p0[] = {halfx, 0.f, -halfz};
        float p1[] = {-halfx, 0.f, -halfz};
        float p2[] = {-halfx, 0.f, p2z};
        float p3[] = {p3x, 0.f, halfz};
        float p4[] = {halfx, 0.f, halfz};
        float p5[] = {topx, h, -topz};
        float p6[] = {-topx, h, -topz};
        float p7[] = {-topx, h, p7z};
        float p8[] = {p8x, h, topz};
        float p9[] = {topx, h, topz};
        float p10[] = {topx, h, 0.f};
        
        glBegin(GL_QUADS); {
            glNormal3f(0.f,1.f,0.f);
            glVertex3fv(p6);
            glVertex3fv(p7);
            glVertex3fv(p10);
            glVertex3fv(p5);
            
            glNormal3f(0.f,1.f,0.f);
            glVertex3fv(p7);
            glVertex3fv(p8);
            glVertex3fv(p9);
            glVertex3fv(p10);
            
            glNormal3f(-1.f,0.f,0.f);
            glVertex3fv(p1);
            glVertex3fv(p2);
            glVertex3fv(p7);
            glVertex3fv(p6);
            
            glNormal3f(-1.f,0.f,1.f);
            glVertex3fv(p3);
            glVertex3fv(p8);
            glVertex3fv(p7);
            glVertex3fv(p2);
            
            glNormal3f(0.f,0.f,1.f);
            glVertex3fv(p3);
            glVertex3fv(p4);
            glVertex3fv(p9);
            glVertex3fv(p8);
            
            glNormal3f(0.f,0.f,-1.f);
            glVertex3fv(p5);
            glVertex3fv(p0);
            glVertex3fv(p1);
            glVertex3fv(p6);
            
            glNormal3f(1.f,0.f,0.f);
            glVertex3fv(p0);
            glVertex3fv(p5);
            glVertex3fv(p9);
            glVertex3fv(p4);
        } glEnd();
    } glPopMatrix();
}

terrarium::terrarium(): airspace(grid(400,8,400)) {
    //quadric = gluNewQuadric();
    
    //Initialize scene variables
    boxxl = 0.f;
    boxxh = 10000.f;
    boxyl = 0.f;
    boxyh = 200.f;
    boxzl = 0.f;
    boxzh = 10000.f;
    ldepth = 4970.f;
    lwidth = 15.f;
    rdepth = 5000.f;
    rwidth = 25.f;
    
    // this is where the bulk of customization is to be made, I have made a few demos
    // flock( airspace,#num of particles,
    //        x,y,z of center spawn, spawn radius,
    //        k_a, k_v, and k_c, acceleration limit,
    //        coordinate of goal pole (y is ignored),
    //        wind, the wind coeficient,
    //        initial starting velocity, tangential acceleration, and initial tangential velocity factor );
    
    /*wind = float3(0.f, 5.f, 0.f);
    windc = 0.f;
    
    flocks.push_back(flock(airspace,150, 4800,100,4200,60, 4.0,0.8,0.08,1000, float3(6000,0,10000), wind,windc, float3(0.0,0.0,80.0),0.0,50.0));
    flocks.push_back(flock(airspace,120, 4200,120,4800,60, 4.0,0.8,0.08,1000, float3(10000,0,6000), wind,windc, float3(80.0,0.0,0.0),0.0,-50.0));*/
    
    wind = float3(-10.f, 100.f, 0.f);
    windc = 0.f;
    
    flocks.push_back(flock(airspace,150, 4800,100,4200,60, 6.0,0.8,0.08,1000, float3(6000,0,10000), wind,windc, float3(0.0,0.0,80.0),-0.1,50.0));

    /*wind = float3(0.f, 0.f, 0.f);
    windc = 0.1f;
    
    flocks.push_back(flock(airspace,80, 4800,100,4200,60, 6.0,0.8,0.08,20, float3(6000,0,10000), wind,windc, float3(0.0,0.0,80.0),0.0,50.0));
    flocks.push_back(flock(airspace,90, 4200,120,4800,60, 4.0,0.8,0.08,20, float3(10000,0,6000), wind,windc, float3(80.0,0.0,0.0),0.0,-50.0));*/
}

/// Integrates all the boids
void terrarium::step(const float t) {
    for (auto &f : flocks)
        f.calc_velocities(airspace, 2, t);
    // this magic number above is the "radius" of the boid influence sphere
    // changing it to be 1 or 3 will increase the sphere, I'd recommend also changing R1 and R2 in birds.h
    
    for (auto &f : flocks)
        f.integrate(t);
    
    airspace.move_birds();
}

/// Draws the scenery and the boids themselves.
void terrarium::draw() const {
    glClearColor(0.7f, 1.f, 1.f, 0.f);
    
    draw_lights();
    draw_ground();
    draw_rock(5300,0,4700,30,70,50,0);
    draw_rock(5290,0,4695,50,50,40,0);
    
    draw_rock(6500,0,5600,45,70,50,75);
    draw_rock(4800,0,7200,35,40,70,165);
    draw_rock(4400,0,5100,30,60,30,40);
    draw_rock(3800,0,3200,20,70,50,90);
    draw_rock(4750,0,4100,50,70,50,300);
    draw_rock(2000,0,5600,60,100,80,45);
    draw_rock(2500,0,4700,40,30,60,200);
    
    for (auto &f : flocks)
        f.draw();
}

float3 terrarium::camera_pos(unsigned int f) const {
    return flocks[f].get_center();
}

float3 terrarium::camera_dir(unsigned int f) const {
    return flocks[f].get_vel().normalize();
}
