///////////////////////////////////////////////
//  flock.cpp                                //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/14/15.  //
///////////////////////////////////////////////

#include "flock.h"

/// Constructor
flock::flock(grid &g, const unsigned long size,
             const float x, const float y, const float z,
             const float radius,
             const float ka, const float kv, const float kc, const float ar,
             float3 goal_,
             float3 w, float wc,
             float3 v, float s_t,
             const float is_t):
    k_a(ka), k_v(kv), k_c(kc),
    a_res(ar), goal(goal_), wind(w), windc(wc), s_tan(s_t)
{
    for (unsigned long i = 0; i < size; i++) {
        auto p = float3::random_in_unit_sphere() * radius;
        
        //tangential vortex force
        auto v_t = (p/radius).cross(v.normalize()) * is_t;
        birds.push_back(bird(float3(x,y,z) + p, v + v_t));
    }
    
    for (auto &b : birds)
        g.add_bird(b.get_pos().x/25, b.get_pos().y/25, b.get_pos().z/25, &b);
}

/// Returns the size of this flock
unsigned long flock::get_size() const { return birds.size(); }


/// Calculates the interactions between boids and applies it to them
void flock::calc_velocities(grid &g, const int radius, const float t) {
    float3 cen(get_center());
    float3 vel(get_vel());
    
    for (auto &b : birds) {
        std::list<bird*> nearby;
        
        int bx = b.get_pos().x/25, by = b.get_pos().y/25, bz = b.get_pos().z/25;
        
        for (int x = std::max(bx - radius, 0); x <= std::min(bx + radius, 400); x++) {
            for (int y = std::max(by - radius, 0); y <= std::min(by + radius, 8); y++) {
                for (int z = std::max(bz - radius, 0); z <= std::min(bz + radius, 400); z++) {
                    if (abs(x-bx) + abs(y-by) + abs(z-bz) <= radius + ((radius+1)/2)) {
                        if (g.get_cell(x,y,z).check())
                            nearby.insert(nearby.begin(), g.get_cell(x,y,z).bird_begin(), g.get_cell(x,y,z).bird_end());
                    }
                }
            }
        }
        
        b.calc_velocity(nearby, k_a, k_v, k_c, a_res, wind, windc, cen, vel, s_tan, goal, t);
    }
}

/// Integrates all boids spawned by this flock
void flock::integrate(const float t) {
    for (auto &b : birds)
        b.integrate(t);
}


/// Calculates and returns the center of mass of this flock
float3 flock::get_center() const {
    float3 center(0.f,0.f,0.f);
    
    for (auto &b : birds)
        center += b.get_pos();
    
    return center / birds.size();
}

/// Calculates and returns the average velocity of this flock
float3 flock::get_vel() const {
    float3 vel(0.f,0.f,0.f);
    
    for (auto &b : birds)
        vel += b.get_vel();
    
    return vel / birds.size();
}


/// Draw all boids spawned by this flock
void flock::draw() const {
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, darkgrey);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, white);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, white);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 1.0);
    
    for (auto &b : birds)
        b.draw();
}
