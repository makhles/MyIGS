// TMatrixBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <algorithm>
#include "TMatrixBuilder.hpp"
#include "TMatrix.hpp"
#include "DeleteList.hpp"

#define PI acos(-1.0)


// Global static pointer to ensure a single instance of the class.
TMatrixBuilder * TMatrixBuilder::m_pInstance = nullptr;


TMatrixBuilder* TMatrixBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new TMatrixBuilder();
    }
    return m_pInstance;
}


TMatrixBuilder::TMatrixBuilder() {
    m_tMatrix = new TMatrix();
}


TMatrixBuilder::~TMatrixBuilder() {
    this->reset();
}


TMatrix* TMatrixBuilder::createTranslationMatrix(double dx, double dy) {
    // Foley (p. 205)
    (*m_tMatrix)(0,0) = 1.0;
    (*m_tMatrix)(0,1) = 0.0;
    (*m_tMatrix)(0,2) = dx;
    (*m_tMatrix)(1,0) = 0.0;
    (*m_tMatrix)(1,1) = 1.0;
    (*m_tMatrix)(1,2) = dy;
    (*m_tMatrix)(2,0) = 0.0;
    (*m_tMatrix)(2,1) = 0.0;
    (*m_tMatrix)(2,2) = 1.0;

    return m_tMatrix;
}


TMatrix* TMatrixBuilder::createScalingMatrix(double sx, double sy, double x, double y) {
    // Foley (p. 209)
    (*m_tMatrix)(0,0) = sx;
    (*m_tMatrix)(0,1) = 0.0;
    (*m_tMatrix)(0,2) = x * (1 - sx);
    (*m_tMatrix)(1,0) = 0.0;
    (*m_tMatrix)(1,1) = sy;
    (*m_tMatrix)(1,2) = y * (1 - sy);
    (*m_tMatrix)(2,0) = 0.0;
    (*m_tMatrix)(2,1) = 0.0;
    (*m_tMatrix)(2,2) = 1.0;

    return m_tMatrix;
}


TMatrix* TMatrixBuilder::createRotationMatrix(double angle, double x, double y) {
    double radians = angle * PI / 180.0;
    double cos_angle = cos (radians);
    double sin_angle = sin (radians);

    // Foley (p. 208)
    // Elements that do not depend on reference point
    (*m_tMatrix)(0,0) = cos_angle;
    (*m_tMatrix)(0,1) = - sin_angle;
    (*m_tMatrix)(0,2) = x * (1.0 - cos_angle) + y * sin_angle;
    (*m_tMatrix)(1,0) = sin_angle;
    (*m_tMatrix)(1,1) = cos_angle;
    (*m_tMatrix)(1,2) = y * (1.0 - cos_angle) - x * sin_angle;
    (*m_tMatrix)(2,0) = 0.0;
    (*m_tMatrix)(2,1) = 0.0;
    (*m_tMatrix)(2,2) = 1.0;

    return m_tMatrix;
}


// Reset all members for creating another matrix.
void TMatrixBuilder::reset() {
    if (m_tMatrix) {
        delete m_tMatrix;
        m_tMatrix = nullptr;
    }
}
