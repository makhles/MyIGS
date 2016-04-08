// Scaling.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef SCALING_HPP
#define SCALING_HPP

#include "TMatrix.hpp"

class Scaling : public TMatrix {
private:
    double m_sx;  // Scaling along the x axis
    double m_sy;  // Scaling along the y axis

public:
    Scaling(unsigned order, double dx, double dy);
    virtual ~Scaling() {}
    void addReferencePoint(const double x, const double y) override;
};

#endif  // SCALING_HPP