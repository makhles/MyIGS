// BezierCurve.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
// 
// This class describes a composite cubic Bézier curve
// with (C1) continuity between each separate curve.

#ifndef BEZIER_CURVE_HPP
#define BEZIER_CURVE_HPP

#include <vector>
#include "Shape.hpp"
#include "Point.hpp"

class BezierCurve : public Shape {
protected:
    std::vector<Point*> m_vertices;

public:
    BezierCurve(const std::string name);
    ~BezierCurve();

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

#endif  // BEZIER_CURVE_HPP