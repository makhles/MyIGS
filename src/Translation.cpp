// Translation.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "Translation.hpp"
#include "TMatrix.hpp"

Translation::Translation(unsigned order, double dx, double dy) :
    TMatrix(order),
    m_dx(dx),
    m_dy(dy)
{

    std::cout << "Before:" << std::endl;

    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            std::cout << "m_matrix[" << i << "][" << j << "] = " << m_matrix[i][j] << std::endl;
        }
    }

    // For now...
    m_matrix[0][0] = 1.0;
    m_matrix[1][1] = 1.0;
    m_matrix[2][2] = 1.0;
    m_matrix[0][1] = 0.0;
    m_matrix[0][2] = dx;
    m_matrix[1][0] = 0.0;
    m_matrix[1][2] = dy;
    m_matrix[2][0] = 0.0;
    m_matrix[2][1] = 0.0;

    std::cout << "After:" << std::endl;

    for (unsigned i = 0; i < m_order; i++) {
        for (unsigned j = 0; j < m_order; j++) {
            std::cout << "m_matrix[" << i << "][" << j << "] = " << m_matrix[i][j] << std::endl;
        }
    }
}
