// TMatrixBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <algorithm>
#include "TMatrixBuilder.hpp"
#include "TMatrix.hpp"
#include "Translation.hpp"
#include "Scaling.hpp"
#include "DeleteList.hpp"

// Global static pointer to ensure a single instance of the class.
TMatrixBuilder * TMatrixBuilder::m_pInstance = nullptr;


TMatrixBuilder* TMatrixBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new TMatrixBuilder();
    }
    return m_pInstance;
}


TMatrixBuilder::TMatrixBuilder() : m_tMatrix(nullptr) {

}


TMatrixBuilder::~TMatrixBuilder() {
    this->reset();
}


void TMatrixBuilder::createTranslationMatrix(double dx, double dy) {
    m_tMatrix = new Translation(3, dx, dy);
}


void TMatrixBuilder::createScalingMatrix(double sx, double sy) {
    m_tMatrix = new Scaling(3, sx, sy);
}


void TMatrixBuilder::createRotationMatrix(double angleZ, TransformationType type) {

}


// Reset all members for creating another matrix.
void TMatrixBuilder::reset() {
    if (m_tMatrix) {
        delete m_tMatrix;
        m_tMatrix = nullptr;
    }
}


TMatrix* TMatrixBuilder::buildMatrix(const double x, const double y) {
    m_tMatrix->addReferencePoint(x, y);
    return m_tMatrix;
}