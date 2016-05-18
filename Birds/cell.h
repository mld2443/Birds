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
    list<bird*> birds;
    float potential;
    
public:
    cell(const float p = 0.0): potential(p) {}
    
    float get_potential() const { return potential; }
    bool check() const { return birds.size(); }
    list<bird*>::iterator bird_begin() { return birds.begin(); }
    list<bird*>::iterator bird_end() { return birds.end(); }
    
    void add_potential(const float p) { potential += p; }
    void add_bird(bird* b) { birds.push_back(b); }
    bird* pop_bird() {
        bird* b = birds.front();
        birds.pop_front();
        return b;
    }
};

#endif /* cell_h */
