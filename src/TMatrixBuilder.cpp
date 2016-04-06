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


TMatrixBuilder::TMatrixBuilder() : m_globalMatrix(nullptr) {

}


void TMatrixBuilder::addTranslation(double dx, double dy) {
    TMatrix *matrix = new Translation(3, dx, dy);
    m_transformations.push_back(matrix);
}


void TMatrixBuilder::addScaling(double sx, double sy) {
    TMatrix *matrix = new Scaling(3, sx, sy);
    m_transformations.push_back(matrix);
}


void TMatrixBuilder::addRotation(double angleZ, TransformationType type) {

}


// Reset all members for creating another matrix.
// Only called if previous matrix was successfully built,
// so there are some pointers that need to be removed from
// the list but not deleted.
void TMatrixBuilder::reset() {
    m_transformations.clear();
}


TMatrixBuilder::~TMatrixBuilder() {
    TMatrixBuilder::rollback();
}


// In case there are any dangling pointers after
// the user has cancelled the matrix creation process.
void TMatrixBuilder::rollback() {
    if (!m_transformations.empty()) {
        std::for_each (m_transformations.begin(),
                       m_transformations.end(),
                       DeleteList<TMatrix*>());
        m_transformations.clear();
        delete m_globalMatrix;
        m_globalMatrix = nullptr;
    }
}


TMatrix* TMatrixBuilder::createMatrix() {

    // Copies the first matrix
    auto matrix = m_transformations.cbegin();
    m_globalMatrix = new TMatrix(**matrix);
    matrix++;

    // Temporary matrix that will receive the result of each multiplication
    TMatrix *temp_matrix = new TMatrix(3);

    while (matrix != m_transformations.cend()) {
        m_globalMatrix->left_product(**matrix, *temp_matrix);
        m_globalMatrix = temp_matrix;
        matrix++;
    }
    return m_globalMatrix;
}

void TMatrixBuilder::addCentroid(const double x, const double y) {
    auto matrix = m_transformations.cbegin();
    while (matrix != m_transformations.cend()) {
        (*matrix)->buildTMatrix(x, y);
        matrix++;
    }
}