// Scaling.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "Scaling.hpp"

Scaling::Scaling(unsigned order, double sx, double sy) :
    TMatrix(order)
{
    // For now...
    m_matrix[0][0] = sx;
    m_matrix[1][1] = sy;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = 0.0;
    m_matrix[0][2] = 0.0;
    m_matrix[1][0] = 0.0;
    m_matrix[1][2] = 0.0;
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;
}


void Scaling::addReferencePoint(const double x, const double y) {
    // TODO
}