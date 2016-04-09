// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange


#ifndef TMATRIX_HPP
#define TMATRIX_HPP

#include <vector>
#include "TransformationType.hpp"

class TMatrix {
protected:
    std::vector<std::vector<double>> m_matrix;
    unsigned m_order; // Number of rows and columns

public:
    TMatrix();
    virtual ~TMatrix();

    // Operators overloading
    double& operator()(const unsigned &row, const unsigned &col);              // Accessor
    const double& operator()(const unsigned &row, const unsigned &col) const;  // Accessor
    void operator*(std::vector<double> &rhs);  // Multiplication by vector
};

#endif  // TMATRIX_HPP