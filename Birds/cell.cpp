///////////////////////////////////////////////
//  cell.cpp                                 //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/15/15.  //
///////////////////////////////////////////////

#include "cell.h"

/// Cell constructor
cell::cell(const float p): m_potential(p) {}


/// Returns potential of this cell
float cell::get_potential() const {
    return m_potential;
}

/// Tests whether this cell has any boids in it
bool cell::check() const {
    return m_birds.size();
}

/// Returns the starting iterator of the current cell
std::list<bird*>::iterator cell::bird_begin() {
    return m_birds.begin();
}

/// Returns the ending iterator of the current cell
std::list<bird*>::iterator cell::bird_end() {
    return m_birds.end();
}


/// Increments the potential of the current cell
void cell::add_potential(const float p) {
    m_potential += p;
}

/// Adds bird to cell
void cell::add_bird(bird* b) {
    m_birds.push_back(b);
}

/// Pops and returns bird from current cell
bird* cell::pop_bird() {
    bird* b = m_birds.front();
    m_birds.pop_front();
    return b;
}
