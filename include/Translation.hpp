// Translation.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSLATION_MATRIX_HPP
#define TRANSLATION_MATRIX_HPP

#include "TMatrix.hpp"

class Translation : public TMatrix {

public:
    Translation(unsigned order, double dx, double dy);
    virtual ~Translation() {}
    void addReferencePoint(const double x, const double y) override;
};

#endif  // TRANSLATION_MATRIX_HPP