//
//  cell.h
//  Birds
//
//  Created by Matthew Dillard on 10/15/15.
//  this is the basic spatial division
//

#ifndef cell_h
#define cell_h

#include <list>
#include "bird.h"

class cell {
private:
    std::list<bird*> m_birds;
    float m_potential;
    
public:
    cell(const float p = 0.0): m_potential(p) {}
    
    float get_potential() const { return m_potential; }
    bool check() const { return m_birds.size(); }
    std::list<bird*>::iterator bird_begin() { return m_birds.begin(); }
    std::list<bird*>::iterator bird_end() { return m_birds.end(); }
    
    void add_potential(const float p) { m_potential += p; }
    void add_bird(bird* b) { m_birds.push_back(b); }
    bird* pop_bird() {
        bird* b = m_birds.front();
        m_birds.pop_front();
        return b;
    }
};

#endif /* cell_h */
