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

    void resize_matrix();

public:
    TMatrix() : TMatrix(3) {}
    TMatrix(int order);
    virtual ~TMatrix() {}

    // Operators overloading
    double& operator()(const unsigned &row, const unsigned &col);
    const double& operator()(const unsigned &row, const unsigned &col) const;
    const TMatrix operator*(const TMatrix &rhs) const;
    void operator*(std::vector<double> &rhs);
    void multiply_by_vector(const std::vector<double>&, std::vector<double>&);
    void multiply_by_scalar(double factor);
};

#endif  // TMATRIX_HPP