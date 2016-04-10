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
    Line(const std::string name, Point *p1, Point *p2);
    ~Line();
    const Point* p1() const { return m_p1; }
    const Point* p2() const { return m_p2; }
    const Coord<double> get_centroid() override;

    // Visitor
    void accept(AbstractDrawer *drawer);

    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void clip_to_window(Window &window) override;
};

#endif  // LINE_HPP