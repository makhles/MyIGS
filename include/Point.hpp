// Point.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef POINT_HPP
#define POINT_HPP

#include <cairomm/context.h>
#include "Shape.hpp"

class Point : public Shape {
private:
    double m_xwc;  // Window x coordinate
    double m_ywc;  // Window y coordinate
    double m_zwc;  // Window z coordinate
    double m_xnc;  // Normalized x coordinate
    double m_ync;  // Normalized y coordinate
    double m_znc;  // Normalized z coordinate

public:
    Point(const std::string &name, double x, double y, double z, const Colour colour = Colour()) :
        Shape(name, ShapeType::POINT, colour),
        m_xwc(x),
        m_ywc(y),
        m_zwc(z) {}
    ~Point() {}

    // Getters
    double xwc() const { return m_xwc; }
    double ywc() const { return m_ywc; }
    double zwc() const { return m_zwc; }
    double xnc() const { return m_xnc; }
    double ync() const { return m_ync; }
    double znc() const { return m_znc; }
    const Coord<double> get_centroid() override;

    // Visitors
    void accept(AbstractDrawer *drawer);
    void clip_to_window(AbstractClipper &clipper) override;

    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void write_to_file(Writer *w) override;

    // Operator overloading
    bool operator==(const Point &rhs) const;
    bool operator!=(const Point &rhs) const;
};

#endif  // POINT_HPP