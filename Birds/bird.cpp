//
//  bird.cpp
//  Birds
//
//  Created by Matthew Dillard on 4/17/18.
//  Copyright © 2018 Matthew Dillard. All rights reserved.
//

#include "bird.h"

/// The custom wind function, it can be any vector field, and wind is the weight of the functions
float3 bird::get_wind(const float3 wind){
    return float3(wind.x,
                  wind.y * sinf((m_pos.x+m_pos.z) * PI/90.f),
                  wind.z);
}


/// Determines how much influence nearby boid applies
float bird::d_coef(const float d) const {
    if (d < R1)
        return 1.f;
    else if (d <= R2)
        return (R2 - d)/(R2 - R1);
    else
        return 0.f;
}

/// Determines how well current boid can see nearby boid
float bird::t_coef(const float angle) const {
    if (-T1 <= angle && angle <= T1)
        return 1.f;
    else if (-T2 <= angle && angle <= T2)
        return (T2 - angle)/(T2 - T1);
    else
        return 0.f;
}

/// Aggregate competing influences for boid.
void bird::aggregate(float3 final_a, float3 final_v, float3 final_c, float a_res) {
    float f_a_len = final_a.abs(), f_v_len = final_v.abs(), f_c_len = final_c.abs();
    
    if (f_a_len > THR) {
        final_a = final_a.normalize() * std::min(a_res, f_a_len);
        a_res -= f_a_len;
    }
    if (f_v_len > THR) {
        final_v = final_v.normalize() * std::min(a_res, f_v_len);
        a_res -= f_v_len;
    }
    if (f_c_len > THR) {
        final_c = final_c.normalize() * std::min(a_res, f_c_len);
    }
    
    m_accel += (final_a + final_v + final_c);
}


/// Constructor
bird::bird(float3 p, float3 v, float m): m_pos(p), m_vel(v), m_accel(0.f), m_mass(m) {}


/// Returns bird's current position
float3 bird::get_pos() const { return m_pos; }

/// Returns bird's current velcity
float3 bird::get_vel() const { return m_vel; }


/// Euler integration of boid's velocity
void bird::integrate(const double t) {
    m_pos += m_vel * t;
}

/// Calculates the velocity of the current bird
void bird::calc_velocity(const std::list<bird*> &nearby,
                         const float ka, const float kv, const float kc, const float a_res,
                         const float3 wind, const float windc,
                         const float3 f_p, const float3 f_v, const float s_tan,
                         float3 goal,
                         const float t) {
    // Vortex force
    float3 v_tan = (m_pos - f_p).cross(f_v).normalize() * s_tan;
    
    // Dynamic wind
    auto w = get_wind(wind);
    m_accel = ((w - m_vel) * (windc/m_mass));
    
    // Calculate affect of nearby boids
    std::list<float3> accel_a, accel_v, accel_c;
    for (auto &neighbor : nearby) {
        if (neighbor != this) {
            auto x = neighbor->m_pos - m_pos;
            auto u_x = x.normalize();
            auto d = x.abs();
            
            float k_dt = d_coef(d) * t_coef(m_vel.angle(x));
            
            accel_a.push_back((u_x * - (ka / d)) * k_dt);
            accel_v.push_back(((neighbor->m_vel - m_vel) * kv) * k_dt);
            accel_c.push_back((x * kc) * k_dt);
        }
    }
    
    // Prepare for acceleration prioritization
    float3 final_a, final_v, final_c;
    for (auto &a : accel_a) final_a += a;
    for (auto &a : accel_v) final_v += a;
    for (auto &a : accel_c) final_c += a;
    
    // Prioritize
    aggregate(final_a, final_v, final_c, a_res);
    
    // Push away from ceiling and floor
    if (m_pos.y < 20.f) m_accel += float3(0.f ,20.f / m_pos.y, 0.f);
    if (m_pos.y > 180.f) m_accel -= float3(0.f ,20.f / (200.f - m_pos.y), 0.f);
    
    // Steer toward a goal
    goal.y = m_pos.y;
    m_accel += (goal - m_pos).normalize() * 5;
    
    // Finally update the velocity
    m_vel += v_tan + m_accel * t;
}


/// Draws this single boid.
void bird::draw() const {
    glPushMatrix(); {
        glTranslatef(m_pos.x, m_pos.y, m_pos.z);
        
        // Size and shape are hard-coded
        
        float3 nose(m_vel.normalize() * 5.f);
        float3 left(m_vel.cross(float3(0.f,-1.f,0.f)).normalize());
        float3 right(m_vel.cross(float3(0.f,1.f,0.f)).normalize());
        float3 norm = right.cross(nose).normalize() * 0.5f;
        float3 left1 = left * 0.2f + norm;
        float3 right1 = right * 0.2f + norm;
        float3 left2 = left + norm;
        float3 right2 = right + norm;
        
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(norm.x, norm.y, norm.z);
            glVertex3f(left1.x, left1.y, left1.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(left2.x, left2.y, left2.z);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(right.x, right.y, right.z);
            glVertex3f(0.f, 0.f, 0.f);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(left1.x, left1.y, left1.z);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(left.x, left.y, left.z);
            glVertex3f(right1.x, right1.y, right1.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(0.f, 0.f, 0.f);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(norm.x, norm.y, norm.z);
            glVertex3f(right2.x, right2.y, right2.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(right1.x, right1.y, right1.z);
        } glEnd();
        
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(-norm.x, -norm.y, -norm.z);
            glVertex3f(left2.x, left2.y, left2.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(left1.x, left1.y, left1.z);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(-right.x, -right.y, -right.z);
            glVertex3f(left1.x, left1.y, left1.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(0.f, 0.f, 0.f);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(-left.x, -left.y, -left.z);
            glVertex3f(0.f, 0.f, 0.f);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(right1.x, right1.y, right1.z);
        } glEnd();
        glBegin(GL_TRIANGLE_STRIP); {
            glNormal3f(-norm.x, -norm.y, -norm.z);
            glVertex3f(right1.x, right1.y, right1.z);
            glVertex3f(nose.x, nose.y, nose.z);
            glVertex3f(right2.x, right2.y, right2.z);
        } glEnd();
    } glPopMatrix();
}
