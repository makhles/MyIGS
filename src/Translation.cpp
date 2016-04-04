// Translation.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "Translation.hpp"
#include "TMatrix.hpp"

Translation::Translation(unsigned order, double dx, double dy) :
    TMatrix(order),
    m_dx(dx),
    m_dy(dy)
{
}
