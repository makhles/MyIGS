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


typedef std::vector<Point*> VPoints;

class WindowClipper : public AbstractClipper {
public:
    WindowClipper();
    ~WindowClipper() {}

    // Overriden virtuan methods
    void clip_to_area(Point &p) override;
    void clip_to_area(Line &line) override;
    void clip_to_area(Wireframe &wf) override;
    void set_line_clipping_method(LineClipping type) override;
    void set_polygon_clipping_method(PolygonClipping type) override;

    // Own methods
    void cohen_sutherland_clipping(Line &line);
    void liang_barsky_clipping(Line &line);
    void nicholl_lee_nicholl_clipping(Line &line);

    void SH_clipping(Wireframe &wf);
    void SH_polygon_clipping(const VPoints&, VPoints&);
    bool SH_inside(Point *p);
    Point* SH_intersect(Point *p, Point *s);

    void weiler_atherton_clipping(Wireframe &wf);

private:
    // Window boundaries coordinates
    const double X_MIN = -1.0;
    const double X_MAX = +1.0;
    const double Y_MIN = -1.0;
    const double Y_MAX = +1.0;

    // Window boundaries (edges)
    enum Boundary {
        TOP,
        BOTTOM,
        LEFT,
        RIGHT
    };
    WindowClipper::Boundary m_edge;
    LineClipping m_lineClipping;        // Type of line clipping
    PolygonClipping m_polygonClipping;  // Type of polygon clipping
};

#endif  // WINDOW_CLIPPER_HPP