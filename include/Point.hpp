// Point.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef POINT_HPP
#define POINT_HPP

#include <cairomm/context.h>
#include "Shape.hpp"

class Point : public Shape {
private:
    double m_xwc;  // Window coordinate
    double m_ywc;  // Window coordinate
    double m_xnc;  // Normalized coordinate
    double m_ync;  // Normalized coordinate

public:
    Point(const std::string name, const double x, const double y);
    ~Point();

    // Getters
    double xwc() const { return m_xwc; }
    double ywc() const { return m_ywc; }
    double xnc() const { return m_xnc; }
    double ync() const { return m_ync; }
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