// WindowClipper.hpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange
// 
// Clips shapes expressed in normalized coordinates to a 
// window whose coordinates are given by the NCS.


#ifndef WINDOW_CLIPPER_HPP
#define WINDOW_CLIPPER_HPP

#include "AbstractClipper.hpp"

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
    void sutherland_hodgeman_clipping(Wireframe &wf);
    void weiler_atherton_clipping(Wireframe &wf);

private:
    const double X_MIN = -1.0;
    const double X_MAX = +1.0;
    const double Y_MIN = -1.0;
    const double Y_MAX = +1.0;
    LineClipping m_lineClipping;
    PolygonClipping m_polygonClipping;
};

#endif  // WINDOW_CLIPPER_HPP