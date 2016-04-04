// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TMatrix.hpp"


// Constructor
TMatrix::TMatrix(unsigned int order) : m_order(order) {

    // Resize number of rows
    m_matrix.resize(m_order);

    // Resize columns and initialize all elements to 0.0
    for (unsigned i = 0; i < m_order; i++) {
        m_matrix[i].resize(m_order, 0.0);
    }
}

// Copy contructor
TMatrix::TMatrix(const TMatrix &rhs) {
    m_matrix = rhs.m_matrix;
    m_order = rhs.getOrder();
}


// Virtual destructor
TMatrix::~TMatrix() {}


// Overloading of the () operator to access individual elements.
double& TMatrix::operator()(const unsigned &row, const unsigned &col) {
    return this->m_matrix[row][col];
}


// Overloading of the () operator to access individual elements (const).
const double& TMatrix::operator()(const unsigned &row, const unsigned &col) const {
    return this->m_matrix[row][col];
}


// Overloading of assignment operator.
// Both matrices must be square and have the same order.
TMatrix& TMatrix::operator=(const TMatrix &rhs) {

    // Perhaps they're already equal
    if (this == &rhs) {
        return *this;
    }

    // Copy of values
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            m_matrix[i][j] = rhs(i,j);
        }
    }

    return *this;
}


// Overloading of * operator.
// Original matrix will be used to store the result.
// Both matrices must be square and have the same order.
void TMatrix::operator*(TMatrix &rhs) {

    TMatrix result(m_order);

    // Multiplication
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            for (unsigned k = 0; k < m_order; k++) {
                result(i,j) = this->m_matrix[i][k] * rhs(i,j);
            }
        }
    }
    rhs = result;  // Copy to original matrix.
}


// Overloading of * operator
// Original vector will be used to store the result.
void TMatrix::operator*(std::vector<double> &rhs) {
    std::vector<double> result(rhs.size());
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            result[i] = this->m_matrix[i][j] * rhs[j];
        }
    }
    rhs = result;
}