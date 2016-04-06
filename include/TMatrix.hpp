// TMatrix.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

// Implementation of an N-order square matrix.

#ifndef TMATRIX_HPP
#define TMATRIX_HPP

#include <vector>

class TMatrix {
protected:
    std::vector<std::vector<double> > m_matrix;

    unsigned m_order; // Number of rows and columns
    double m_refX;    // X coordinate of reference point
    double m_refY;    // Y coordinate of reference point

public:
    TMatrix(unsigned order);
    TMatrix(const TMatrix &rhs);  // Copy constructor
    virtual ~TMatrix();

    // Operators overloading
    double& operator()(const unsigned &row, const unsigned &col);              // Accessor
    const double& operator()(const unsigned &row, const unsigned &col) const;  // Accessor
    TMatrix& operator=(const TMatrix &rhs);    // Assignment
    void operator*(TMatrix &rhs);              // Multiplication by matrix
    void operator*(std::vector<double> &rhs);  // Multiplication by vector

    // Getters
    unsigned getOrder() const { return m_order;}
    //virtual void rebuildTMatrix(TMatrix *) {}
};

#endif  // TMATRIX_HPP