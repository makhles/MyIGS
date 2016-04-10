// TMatrixBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <algorithm>
#include "TMatrixBuilder.hpp"
#include "TMatrix.hpp"

#define PI acos(-1.0)


// Global static pointer to ensure a single instance of the class.
TMatrixBuilder * TMatrixBuilder::m_pInstance = nullptr;


TMatrixBuilder* TMatrixBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new TMatrixBuilder();
    }
    return m_pInstance;
}


void TMatrixBuilder::translation_matrix(TMatrix &m, double dx, double dy) {
    // Foley (p. 205)
    m(0,0) = 1.0;
    m(0,1) = 0.0;
    m(0,2) = dx;
    m(1,0) = 0.0;
    m(1,1) = 1.0;
    m(1,2) = dy;
    m(2,0) = 0.0;
    m(2,1) = 0.0;
    m(2,2) = 1.0;
}


void TMatrixBuilder::scaling_matrix(TMatrix &m, double sx, double sy, double x, double y) {
    // Foley (p. 209)
    m(0,0) = sx;
    m(0,1) = 0.0;
    m(0,2) = x * (1 - sx);
    m(1,0) = 0.0;
    m(1,1) = sy;
    m(1,2) = y * (1 - sy);
    m(2,0) = 0.0;
    m(2,1) = 0.0;
    m(2,2) = 1.0;
}


void TMatrixBuilder::rotation_matrix(TMatrix &m, double angle, double x, double y) {
    double radians = angle * PI / 180.0;
    double cos_angle = cos (radians);
    double sin_angle = sin (radians);

    // Foley (p. 208)
    m(0,0) = cos_angle;
    m(0,1) = - sin_angle;
    m(0,2) = x * (1.0 - cos_angle) + y * sin_angle;
    m(1,0) = sin_angle;
    m(1,1) = cos_angle;
    m(1,2) = y * (1.0 - cos_angle) - x * sin_angle;
    m(2,0) = 0.0;
    m(2,1) = 0.0;
    m(2,2) = 1.0;
}


void TMatrixBuilder::normalizing_matrix(TMatrix &m, double dx, double dy, double sx,
            double sy, double angle) {

    double radians = angle * PI / 180.0;
    double cos_angle = cos (radians);
    double sin_angle = sin (radians);
    double sx_sin = sx * sin_angle;
    double sx_cos = sx * cos_angle;
    double sy_sin = sy * sin_angle;
    double sy_cos = sy * cos_angle;

    m(0,0) = sx_cos;
    m(0,1) = - sy_sin;
    m(0,2) = sx_cos * dx - sy_sin * dy;
    m(1,0) = sx_sin;
    m(1,1) = sy_cos;
    m(1,2) = sx_sin * dx + sy_cos * dy;
    m(2,0) = 0.0;
    m(2,1) = 0.0;
    m(2,2) = 1.0;
}