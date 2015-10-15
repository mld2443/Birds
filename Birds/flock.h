//
//  flock.h
//  Birds
//
//  Created by Matthew Dillard on 10/14/15.
//

#ifndef flock_h
#define flock_h

#include <vector>
#include <math.h>
#include <random>
#include <stdlib.h>
#include "grid.h"

const GLfloat darkgrey[] = { 0.2, 0.2, 0.2 };
const GLfloat grey[] = { 0.6, 0.6, 0.6 };
const GLfloat white[] = { 1.0, 1.0, 1.0 };

class flock {
private:
    vector<bird> birds;
    float k_a, k_v, k_c;
    v3<double> wind, goal;
    float windc, s_tan;
    
    default_random_engine eng;
        
    v3<double> spawn_p(const float x, const float y, const float z, const float d) {
        uniform_real_distribution<float> U11(-1.0, 1.0);
        auto Y = U11(eng);
        uniform_real_distribution<float> Upp(-PI,PI);
        auto T = Upp(eng);
        
        auto R = sqrt(1 - Y*Y);
        
        v3<double> pshpere(R * cos(T), Y, R * sin(T));
        
        return v3<double>(x,y,z) + pshpere * d;
    }
    
public:
    flock(grid &g, const unsigned long size,
          const float x, const float y, const float z,
          const float d,
          const float ka, const float kv, const float kc,
          v3<double> goal_,
          v3<double> w = v3<double>(), double wc = 0.0,
          v3<double> v = v3<double>(), double s_t = 0.0): k_a(ka), k_v(kv), k_c(kc), goal(goal_), wind(w), windc(wc), s_tan(s_t)
    {
        for (unsigned long i = 0; i < size; i++)
            birds.push_back(bird(spawn_p(x,y,z,d), v));
        for (auto &b : birds)
            g.add_bird(b.get_pos().x/25, b.get_pos().y/25, b.get_pos().z/25, &b);
    }
    
    unsigned long get_size() const { return birds.size(); }
    
    void calc_velocities(grid &g, const int radius, const double t) {
        v3<double> cen(get_center());
        v3<double> vel(get_vel());
        for (auto &b : birds) {
            list<bird*> nearby;
            
            int bx = b.get_pos().x/25, by = b.get_pos().y/25, bz = b.get_pos().z/25;
            
            for (int x = max(bx - radius, 0); x <= min(bx + radius, 400); x++)
                for (int y = max(by - radius, 0); y <= min(by + radius, 8); y++)
                    for (int z = max(bz - radius, 0); z <= min(bz + radius, 400); z++)
                        if (abs(x-bx) + abs(y-by) + abs(z-bz) <= radius + ((radius+1)/2))
                            if (g.get_cell(x,y,z).check())
                                nearby.insert(nearby.begin(), g.get_cell(x,y,z).bird_begin(), g.get_cell(x,y,z).bird_end());
            
            b.calc_velocity(nearby, k_a, k_v, k_c, wind, windc, cen, vel, s_tan, goal, t);
        }
    }
    
    void integrate(const float t) { for (auto &b : birds) b.integrate(t); }
    
    v3<double> get_center() {
        v3<double> center(0.0,0.0,0.0);
        for (auto &b : birds) center += (b.get_pos() / birds.size());
        return center;
    }
    
    v3<double> get_vel() {
        v3<double> vel(0.0,0.0,0.0);
        for (auto &b : birds) vel += (b.get_vel() / birds.size());
        return vel;
    }
    
    void draw() const {
        glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkgrey);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
        for (auto &b : birds) b.draw();
    }
};

#endif /* flock_h */
