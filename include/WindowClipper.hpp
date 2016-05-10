// WindowClipper.hpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange
// 
// Clips shapes expressed in normalized coordinates to a 
// window whose coordinates are given by the NCS.


#ifndef WINDOW_CLIPPER_HPP
#define WINDOW_CLIPPER_HPP

#include <vector>
#include "AbstractClipper.hpp"

// Forward declarations
template <class T> class Coord;

// Definitions
typedef std::vector<Coord<double>*> DCoordVector;


class WindowClipper : public AbstractClipper {
public:
    WindowClipper();
    ~WindowClipper() {}

    // Overriden virtual methods
    void clip_to_area(Point &p) override;
    void clip_to_area(Line &line) override;
    void clip_to_area(Wireframe &wf) override;
    void clip_to_area(Curve2D &curve) override;
    void set_line_clipping_method(LineClipping type) override;
    void set_polygon_clipping_method(PolygonClipping type) override;

    // Own methods ----------------

    // Cohen-Sutherland methods
    void cohen_sutherland_clipping(Line &line);
    int computeOutcode(double x, double y);

    void liang_barsky_clipping(Line &line);
    void nicholl_lee_nicholl_clipping(Line &line);

    // Sutherland-Hodgeman methods
    void SH_clipping(Wireframe &wf);
    void SH_polygon_clipping(const DCoordVector&, DCoordVector&);
    bool SH_inside(Coord<double> *p);
    Coord<double>* SH_intersect(Coord<double> *p, Coord<double> *s);

    // Weiler-Atherton methods
    void weiler_atherton_clipping(Wireframe &wf);

    // Bézier methods
    bool coord_inside(double x, double y);

private:
    // Window boundaries coordinates
    const double X_MIN = -1.0;
    const double X_MAX = +1.0;
    const double Y_MIN = -1.0;
    const double Y_MAX = +1.0;

    // Used on Cohen-Sutherland
    const int INSIDE = 0;
    const int LEFT = 1;
    const int RIGHT = 2;
    const int BOTTOM = 4;
    const int TOP = 8;

    // Window boundaries (edges)
    enum Boundary {
        TOP_EDGE,
        BOTTOM_EDGE,
        LEFT_EDGE,
        RIGHT_EDGE
    };
    WindowClipper::Boundary m_edge;
    LineClipping m_lineClipping;        // Type of line clipping
    PolygonClipping m_polygonClipping;  // Type of polygon clipping

    void clip_bezier_curve(const DCoordVector &inVertices, DCoordVector &outVertices);
    void clip_bspline(const DCoordVector &inVertices, DCoordVector &outVertices);
};

#endif  // WINDOW_CLIPPER_HPP