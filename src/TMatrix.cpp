// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TMatrix.hpp"

// For debugging, uncomment the following define
//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

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
const TMatrix TMatrix::operator*(const TMatrix &rhs) const
/* ============================================================================================= */
{
    // Overloading of * operator
    TMatrix result(4);
    double sum;
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            sum = 0.0;
            for (unsigned k = 0; k < m_order; k++) {
                sum += this->m_matrix[i][k] * rhs(k,j);
            }
            result(i,j) = sum;
        }
    }
    return result;
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
    DEBUG_MSG("Matrix multiplication by vector");
    DEBUG_MSG("Matrix order: " << m_order);
    DEBUG_MSG("Vector order: " << result.size());
    double tmp;
    for (unsigned i = 0; i < m_order; i++) {
        tmp = 0.0;
        for (unsigned j = 0; j < m_order; j++) {
            tmp += this->m_matrix[i][j] * rhs[j];
            DEBUG_MSG("tmp = " << tmp);
        }
        result.push_back(tmp);
    }
}


/* ============================================================================================= */
void TMatrix::multiply_by_scalar(double factor)
/* ============================================================================================= */
{
    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            this->m_matrix[i][j] *= factor;
        }
    }
}