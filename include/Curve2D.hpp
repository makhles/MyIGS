// Curve2D.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange


#ifndef CURVE_2D_HPP
#define CURVE_2D_HPP

#include <vector>
#include "Shape.hpp"
#include "Point.hpp"

class Curve2D : public Shape {
protected:
    std::vector<Point*> m_vertices;

public:
    Curve2D(const std::string name, ShapeType type, const Colour colour = Colour()) :
        Shape(name, type, colour) {}
    ~Curve2D();

    const Coord<double> get_centroid() override;
    void add_point(Point *point);

    const std::vector<Point*>& vertices() const { return m_vertices; }

    // Visitors
    void accept(AbstractDrawer *drawer);
    void clip_to_window(AbstractClipper &clipper) override;

    void transform(TMatrix &matrix) override;
    void normalize(TMatrix &matrix) override;
    void write_to_file(Writer *w) override;
};

#endif  // CURVE_2D_HPP