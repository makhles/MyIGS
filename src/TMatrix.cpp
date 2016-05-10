// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TMatrix.hpp"


/* ============================================================================================= */
TMatrix::TMatrix(int order) : m_order(order)
/* ============================================================================================= */
{
    this->resize_matrix();
}

/* ============================================================================================= */
void TMatrix::resize_matrix()
/* ============================================================================================= */
{
    m_matrix.resize(m_order);

    // Resize columns and initialize all elements to 0.0
    for (unsigned i = 0; i < m_order; i++) {
        m_matrix[i].resize(m_order, 0.0);
    }
}

/* ============================================================================================= */
double& TMatrix::operator()(const unsigned &row, const unsigned &col)
/* ============================================================================================= */
{
    // Overloading of the () operator to access individual elements.
    return this->m_matrix[row][col];
}

/* ============================================================================================= */
const double& TMatrix::operator()(const unsigned &row, const unsigned &col) const
/* ============================================================================================= */
{
    // Overloading of the () operator to access individual elements (const).
    return this->m_matrix[row][col];
}

/* ============================================================================================= */
void TMatrix::operator*(std::vector<double> &rhs)
/* ============================================================================================= */
{
    // Overloading of * operator
    // Original vector will be used to store the result.
    std::vector<double> result(rhs.size());
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            result[i] += this->m_matrix[i][j] * rhs[j];
        }
    }
    rhs = result;
}

/* ============================================================================================= */
void TMatrix::multiply_by_vector(const std::vector<double> &rhs, std::vector<double> &result)
/* ============================================================================================= */
{
    for (unsigned i = 0; i < m_order; i++) {
        result[i] = 0.0;
        for (unsigned j = 0; j < m_order; j++) {
            result[i] += this->m_matrix[i][j] * rhs[j];
        }
    }
}