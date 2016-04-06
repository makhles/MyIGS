// Translation.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSLATION_MATRIX_HPP
#define TRANSLATION_MATRIX_HPP

#include "TMatrix.hpp"

class Translation : public TMatrix {
private:
    double m_dx;  // Translation along the x axis
    double m_dy;  // Translation along the y axis

public:
    Translation(unsigned order, double dx, double dy);
    virtual ~Translation() {}
    //virtual void rebuildTMatrix(TMatrix *);
};

#endif  // TRANSLATION_MATRIX_HPP