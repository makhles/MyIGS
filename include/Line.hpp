// Line.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef LINE_HPP
#define LINE_HPP

#include "Shape.hpp"

// Forward declarations
class Point;


class Line : public Shape {
protected:
    Point *m_p1;
    Point *m_p2;

public:
    Line(const std::string name, Point *p1, Point *p2, const Colour colour = Colour()) :
        Shape(name, ShapeType::LINE, colour),
        m_p1(p1),
        m_p2(p2) {}
    ~Line() {}
    Point* p1() const { return m_p1; }
    Point* p2() const { return m_p2; }
    const Coord<double> get_centroid() override;

    // Visitors
    void accept(AbstractDrawer *drawer);
    void clip_to_window(AbstractClipper &clipper) override;

    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void write_to_file(Writer *w) override;
};

#endif  // LINE_HPP