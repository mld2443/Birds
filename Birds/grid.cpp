///////////////////////////////////////////////
//  grid.cpp                                 //
//  Birds                                    //
//                                           //
//  Created by Matthew Dillard on 10/14/15.  //
///////////////////////////////////////////////

#include "grid.h"

/// Constructor
grid::grid(const unsigned int w, const unsigned int h, const unsigned int l):
    m_cells(std::vector<std::vector<std::vector<cell>>>(w, std::vector<std::vector<cell>>(h, std::vector<cell>(l, 0.f)))),
    m_record(std::list<std::tuple<int,int,int>>()) {
    // Add potential to cells next to the ground so
    // boids will fly upwards if they stray too low
    for (int x = 0; x < w; x++)
        for (int z = 0; z < l; z++)
            m_cells[x][0][z].add_potential(25.f);
}

/// Adds a boid to its respective grid
void grid::add_bird(const int x, const int y, const int z, bird* b) {
    m_record.push_back(std::make_tuple(x,y,z));
    m_cells[x][y][z].add_bird(b);
}

/// Updates all boids at once
void grid::move_birds() {
    std::vector<bird*> phase;
    for (auto &b : m_record)
        phase.push_back(m_cells[std::get<0>(b)][std::get<1>(b)][std::get<2>(b)].pop_bird());
    
    m_record.clear();
    
    for (auto &b : phase){
        int x = b->get_pos().x/25, y = b->get_pos().y/25, z = b->get_pos().z/25;
        if (x < 0) { x = 0; }
        if (x >= m_cells.size()) { x = (int) m_cells.size() - 1; }
        if (y < 0) { y = 0; }
        if (y > m_cells[0].size()) { y = (int) m_cells[0].size() - 1; }
        if (z < 0) { z = 0; }
        if (z > m_cells[0][0].size()) { z = (int) m_cells[0][0].size() - 1; }
        m_record.push_back(std::make_tuple(x,y,z));
        m_cells[x][y][z].add_bird(b);
    }
}

/// Returns cell at specified coordinates
cell& grid::get_cell(int x, int y, int z) {
    if (x < 0) { x = 0; }
    if (x >= m_cells.size()) { x = (int) m_cells.size() - 1; }
    if (y < 0) { y = 0; }
    if (y > m_cells[0].size()) { y = (int) m_cells[0].size() - 1; }
    if (z < 0) { z = 0; }
    if (z > m_cells[0][0].size()) { z = (int) m_cells[0][0].size() - 1; }
    return m_cells[x][y][z];
}
