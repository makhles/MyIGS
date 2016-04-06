// TMatrixBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <algorithm>
#include "TMatrixBuilder.hpp"
#include "TMatrix.hpp"
#include "Translation.hpp"
#include "DeleteList.hpp"

// Global static pointer to ensure a single instance of the class.
TMatrixBuilder * TMatrixBuilder::m_pInstance = nullptr;


TMatrixBuilder* TMatrixBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new TMatrixBuilder();
    }
    return m_pInstance;
}


void TMatrixBuilder::addTranslation(double dx, double dy) {
    TMatrix *matrix = new Translation(3, dx, dy);
    m_transformations.push_back(matrix);
}


void TMatrixBuilder::addScaling(double sx, double sy) {

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
    }
}


TMatrix* TMatrixBuilder::createMatrix() {
    auto matrix = m_transformations.cbegin();
    TMatrix *global_matrix = new TMatrix(**matrix);  // Copies the first matrix
    matrix++;
    while (matrix != m_transformations.cend()) {
        (**matrix) * (*global_matrix);  // Global matrix receives the result
        matrix++;
    }
    return global_matrix;
}