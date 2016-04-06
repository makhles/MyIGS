// Translation.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Translation.hpp"
#include "TMatrix.hpp"

Translation::Translation(unsigned order, double dx, double dy) :
    TMatrix(order)
{
    // For now...
    m_matrix[0][0] = 1.0;
    m_matrix[1][1] = 1.0;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = 0.0;
    m_matrix[0][2] = dx;
    m_matrix[1][0] = 0.0;
    m_matrix[1][2] = dy;
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;
}


void Translation::buildTMatrix(const double ref_x, const double ref_y) {
    // Nothing to do here.
}