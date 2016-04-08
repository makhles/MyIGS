// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

// Implementation of an N-order square matrix.

#ifndef TMATRIX_HPP
#define TMATRIX_HPP

#include <vector>
#include "TransformationType.hpp"

class TMatrix {
protected:
    std::vector<std::vector<double> > m_matrix;
    unsigned m_order; // Number of rows and columns
    TransformationType m_type;

public:
    TMatrix(unsigned order);
    TMatrix(const TMatrix &rhs);  // Copy constructor
    virtual ~TMatrix();

    // Operators overloading
    double& operator()(const unsigned &row, const unsigned &col);              // Accessor
    const double& operator()(const unsigned &row, const unsigned &col) const;  // Accessor
    void operator*(std::vector<double> &rhs);  // Multiplication by vector

    // Getters
    unsigned getOrder() const { return m_order; }
    TransformationType getType() const { return m_type; }

    virtual void addReferencePoint(const double, const double) = 0;
};

#endif  // TMATRIX_HPP