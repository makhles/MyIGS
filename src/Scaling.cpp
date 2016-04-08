// Scaling.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "Scaling.hpp"

Scaling::Scaling(unsigned order, double sx, double sy) :
    TMatrix(order),
    m_sx(sx),
    m_sy(sy)
{
    // For now...
}


void Scaling::addReferencePoint(const double x, const double y) {
    // Foley (p. 209)
    m_matrix[0][0] = m_sx;
    m_matrix[1][1] = m_sy;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = 0.0;
    m_matrix[0][2] = x * (1 - m_sx);
    m_matrix[1][0] = 0.0;
    m_matrix[1][2] = y * (1 - m_sy);
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;
}