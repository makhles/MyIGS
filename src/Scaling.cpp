// Scaling.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Scaling.hpp"
#include "TMatrix.hpp"
#include "Translation.hpp"

Scaling::Scaling(unsigned order, double sx, double sy) :
    TMatrix(order)
{
    // For now...
    m_matrix[0][0] = sx;
    m_matrix[1][1] = sy;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = 0.0;
    m_matrix[0][2] = 0.0;
    m_matrix[1][0] = 0.0;
    m_matrix[1][2] = 0.0;
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;
}


// Creates two additional translation matrix so that the 
// scaling is relative to the object's centroid.
//
//  scaling_matrix = mtx_left * m_matrix * mtx_right
//
void Scaling::buildTMatrix(const double ref_x, const double ref_y) {
    TMatrix *mtx_right = new Translation(m_order, -ref_x, -ref_y);
    TMatrix *mtx_left = new Translation(m_order, ref_x, ref_y);
    TMatrix *mtx_temp = new TMatrix(m_order);
    TMatrix *mtx_this = this;  // Operators not overloaded for Scaling

    // Right multiplication
    (*mtx_this).right_product(*mtx_right, *mtx_temp);
    (*mtx_this) = *mtx_temp;

    // Left multiplication
    (*mtx_this).left_product(*mtx_left, *mtx_temp);
    (*mtx_this) = *mtx_temp;

    // Get rid of them
    delete mtx_right;
    delete mtx_left;
    delete mtx_temp;
}