//
//  terrarium.cpp
//  Flocks
//
//  Created by Matthew Dillard on 10/12/15.
//

#pragma GCC diagnostic ignored "-Wdeprecated-declarations"

#include "terrarium.h"

void terrarium::draw_lights() {
    // Set up lights
    GLfloat light0color[] = { 0.8, 0.8, 0.7 };
    //GLfloat light0color[] = { 1, 1, 1 };
    GLfloat light0pos[] = { 500, 500, 0 };
    GLfloat light1color[] = { 0.4, 0.4, 0.2 };
    GLfloat light1pos[] = { 303, 300, 300 };
    glLightfv(GL_LIGHT0, GL_POSITION, light0pos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light0color);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light0color);
    glLightfv(GL_LIGHT1, GL_POSITION, light1pos);
    glLightfv(GL_LIGHT1, GL_AMBIENT, light1color);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, light1color);
    glLightfv(GL_LIGHT1, GL_SPECULAR, light1color);
}

void terrarium::draw_bounds() {
    //Draw the box
    GLfloat white[] = { 1.0, 1.0, 1.0 };
    
    glBegin(GL_LINE_STRIP);
    //bottom face
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxh, boxyl, boxzh);
    glVertex3f(boxxh, boxyl, boxzl);
    glVertex3f(boxxl, boxyl, boxzl);
    glVertex3f(boxxl, boxyl, boxzh);
    glVertex3f(boxxh, boxyl, boxzh);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    //top face
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxh, boxyh, boxzh);
    glVertex3f(boxxl, boxyh, boxzh);
    glVertex3f(boxxl, boxyh, boxzl);
    glVertex3f(boxxh, boxyh, boxzl);
    glVertex3f(boxxh, boxyh, boxzh);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    //back left
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxl, boxyl, boxzl);
    glVertex3f(boxxl, boxyh, boxzl);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    //back right
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxh, boxyl, boxzl);
    glVertex3f(boxxh, boxyh, boxzl);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    //front right
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxh, boxyl, boxzh);
    glVertex3f(boxxh, boxyh, boxzh);
    glEnd();
    
    glBegin(GL_LINE_STRIP);
    //front left
    glMaterialfv(GL_FRONT, GL_AMBIENT, white);
    glVertex3f(boxxl, boxyl, boxzh);
    glVertex3f(boxxl, boxyh, boxzh);
    glEnd();
}

void terrarium::draw_ground() {
    GLfloat gnd_ambient[] = { 0.9, 0.8, 0.5 };
    GLfloat gnd_diffuse[] = { 0.0, 0.0, 0.0 };
    GLfloat gnd_specular[] = { 0.0, 0.0, 0.0 };
    GLfloat gnd_shininess[] = { 0.0 };
    
    GLfloat water_ambient[] = { 0.0, 0.0, 0.0 };
    GLfloat water_diffuse[] = { 0.0, 0.0, 0.0 };
    GLfloat water_specular[] = { 0.5, 0.5, 1.0 };
    GLfloat water_shininess[] = { 0.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, gnd_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, gnd_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, gnd_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, gnd_shininess);
    
    glBegin(GL_QUADS); {
        glNormal3f(0,1,0);
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
        glNormal3f(0,1,0);
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
        glNormal3f(0,1,0);
        glVertex3f(boxxl, boxyl, boxzl);
        glVertex3f(boxxl, boxyl, ldepth - lwidth);
        glVertex3f(boxxh, boxyl, rdepth - rwidth);
        glVertex3f(boxxh, boxyl, boxzl);
    } glEnd();
}

void terrarium::draw_tree(const float x, const float y, const float z) {
    GLfloat tree_ambient[] = { 0.05, 0.05, 0.05 };
    GLfloat tree_diffuse[] = { 0.3, 0.3, 0.3 };
    GLfloat tree_specular[] = { 0.3, 0.3, 0.3 };
    GLfloat tree_shininess[] = { 1.0 };
    
    GLfloat leaf_ambient[] = { 0.0, 0.0, 0.0 };
    GLfloat leaf_diffuse[] = { 0.3, 0.5, 0.3 };
    GLfloat leaf_specular[] = { 0.1, 0.3, 0.1 };
    GLfloat leaf_shininess[] = { 10.0 };
    
    glPushMatrix(); {
        glTranslatef(x, y, z);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, tree_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, tree_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, tree_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, tree_shininess);
        
        glPushMatrix(); {
            glRotatef(-90, 1, 0, 0);
            gluCylinder(quadric, 20, 15, 60, 32, 32);
            
            glTranslatef(0, 0, 60);
            gluCylinder(quadric, 15, 15, 100, 32, 32);
        } glPopMatrix();
        
        glTranslatef(0, 160, 0);
        
        glMaterialfv(GL_FRONT, GL_AMBIENT, leaf_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, leaf_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, leaf_specular);
        glMaterialfv(GL_FRONT, GL_SHININESS, leaf_shininess);
        
        for (int i = 0; i < 360; i += 360/6) {
            glPushMatrix(); {
                glRotatef(i, 0, 1, 0);
                glTranslatef(40, 0, 0);
                glutSolidSphere(60, 64, 64);
            } glPopMatrix();
        }
        glTranslatef(0, 40, 0);
        glutSolidSphere(60, 64, 64);
        
    } glPopMatrix();
}

void terrarium::draw_rock(const int x, const int y, const int z, const float h, const int w, const int l, const int r) {
    //int cell[] = {x/25, y/25, z/25};
    
    GLfloat rock_ambient[] = { 0.2, 0.2, 0.2 };
    GLfloat rock_diffuse[] = { 0.9, 0.9, 0.9 };
    GLfloat rock_specular[] = { 0.5, 0.5, 0.5 };
    GLfloat rock_shininess[] = { 1.0 };
    
    glMaterialfv(GL_FRONT, GL_AMBIENT, rock_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, rock_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, rock_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, rock_shininess);
    
    float topx = w / 3, topz = l / 3;
    float halfx = w / 2, halfz = l / 2;
    float p2z = (2 * l / 3) - halfz, p3x = halfx - (2 * w / 3);
    float p7z = (4 * l / 9) - topz, p8x = topx - (4 * w / 9);
    
    glPushMatrix(); {
        glTranslatef(x, y, z);
        glRotatef(r, 0, 1, 0);
        
        float p0[] = {halfx, 0, -halfz};
        float p1[] = {-halfx, 0, -halfz};
        float p2[] = {-halfx, 0, p2z};
        float p3[] = {p3x, 0, halfz};
        float p4[] = {halfx, 0, halfz};
        float p5[] = {topx, h, -topz};
        float p6[] = {-topx, h, -topz};
        float p7[] = {-topx, h, p7z};
        float p8[] = {p8x, h, topz};
        float p9[] = {topx, h, topz};
        float p10[] = {topx, h, 0};
        
        glBegin(GL_QUADS); {
            glNormal3f(0,1,0);
            glVertex3fv(p6);
            glVertex3fv(p7);
            glVertex3fv(p10);
            glVertex3fv(p5);
            
            glNormal3f(0,1,0);
            glVertex3fv(p7);
            glVertex3fv(p8);
            glVertex3fv(p9);
            glVertex3fv(p10);
            
            glNormal3f(-1,0,0);
            glVertex3fv(p1);
            glVertex3fv(p2);
            glVertex3fv(p7);
            glVertex3fv(p6);
            
            glNormal3f(-1,0,1);
            glVertex3fv(p3);
            glVertex3fv(p8);
            glVertex3fv(p7);
            glVertex3fv(p2);
            
            glNormal3f(0,0,1);
            glVertex3fv(p3);
            glVertex3fv(p4);
            glVertex3fv(p9);
            glVertex3fv(p8);
            
            glNormal3f(0,0,-1);
            glVertex3fv(p5);
            glVertex3fv(p0);
            glVertex3fv(p1);
            glVertex3fv(p6);
            
            glNormal3f(1,0,0);
            glVertex3fv(p0);
            glVertex3fv(p5);
            glVertex3fv(p9);
            glVertex3fv(p4);
        } glEnd();
    } glPopMatrix();
}

terrarium::terrarium() {
    quadric = gluNewQuadric();
    
    //Initialize scene variables
    boxxl = 0;
    boxxh = 10000;
    boxyl = 0;
    boxyh = 200;
    boxzl = 0;
    boxzh = 10000;
    ldepth = 4970;
    lwidth = 15;
    rdepth = 5000;
    rwidth = 25;
    
    for (int x = 0; x < 400; x++) {
        airspace.push_back(vector<vector<grid>>(8, vector<grid>(400, grid())));
        for (int z = 0; z < 400; z++)
            airspace[x][0][z].add_potential(25);
    }
    
    flocks.push_back(flock(airspace,100,5000,100,5000,30,v3f(0,0,-5)));
}

void terrarium::step(const float t) {
    for (auto &f : flocks)
        f.calc_velocities(airspace, t);
}

void terrarium::draw() {
    glClearColor(0.7, 1.0, 1.0, 0.0);
    
    draw_lights();
    draw_ground();
    //draw_tree(5070, 0, 5055);
    draw_rock(4700,0,4700,30,70,50,0);
    draw_rock(4710,0,4695,50,50,40,0);
    draw_rock(6500,0,5600,45,70,50,75);
    draw_rock(4400,0,5100,30,60,30,40);
    draw_rock(3800,0,3200,20,70,50,90);
    draw_rock(4750,0,4100,50,70,50,300);
    
    draw_rock(2000,0,5600,60,100,80,45);
    draw_rock(2500,0,4700,40,30,60,200);
    
    for (auto &f : flocks)
        f.draw();
}
