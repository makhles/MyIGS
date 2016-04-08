// Rotation.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <math.h>
#include "Rotation.hpp"

#define PI acos(-1.0)

Rotation::Rotation(unsigned order, double angle, double x, double y) :
    TMatrix(order),
    m_angle(angle),
    m_x(x),
    m_y(y),
    m_centroid(false)
{
    // For now...
}


Rotation::Rotation(unsigned order, double angle) :
    TMatrix(order),
    m_angle(angle),
    m_centroid(true)
{

}


void Rotation::addReferencePoint(const double x, const double y) {
    double radians = m_angle * PI / 180.0;
    double cos_angle = cos (radians);
    double sin_angle = sin (radians);

    // Foley (p. 208)
    // Elements that do not depend on reference point
    m_matrix[0][0] = cos_angle;
    m_matrix[1][1] = cos_angle;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = - sin_angle;
    m_matrix[1][0] = sin_angle;
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;

    // Elements that depend on the reference point
    if (m_centroid) {
        m_matrix[0][2] = x * (1.0 - cos_angle) + y * sin_angle;
        m_matrix[1][2] = y * (1.0 - cos_angle) - x * sin_angle;
    } else {
        m_matrix[0][2] = m_x * (1.0 - cos_angle) + m_y * sin_angle;
        m_matrix[1][2] = m_y * (1.0 - cos_angle) - m_x * sin_angle;
    }
}