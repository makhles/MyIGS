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
    const double xwc() const { return m_xwc; }
    const double ywc() const { return m_ywc; }
    const double xnc() const { return m_xnc; }
    const double ync() const { return m_ync; }
    const Coord<double> get_centroid() override;

    // Visitor
    void accept(AbstractDrawer *drawer);
    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void clip_to_window(Window &window) override;
    void write_to_file(Writer *w) override;

    // Operator overloading
    bool operator==(const Point &rhs) const;
    bool operator!=(const Point &rhs) const;
};

#endif  // POINT_HPP