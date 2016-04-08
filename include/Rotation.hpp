// Rotation.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef ROTATION_HPP
#define ROTATION_HPP

#include "TMatrix.hpp"

class Rotation : public TMatrix {
private:
    double m_angle;   // Rotation angle in degrees
    double m_x;       // X-coord of the reference point
    double m_y;       // Y-coord of the reference point
    bool m_centroid;  // Rotation about centroid

public:
    Rotation(unsigned order, double angle, double x, double y);
    Rotation(unsigned order, double angle);
    virtual ~Rotation() {}
    void addReferencePoint(const double x, const double y) override;
};

#endif  // ROTATION_HPP