// AbstractClipper.hpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#ifndef ABSTRACT_CLIPPER_HPP
#define ABSTRACT_CLIPPER_HPP

#include "ClippingType.hpp"

// Forward declarations
class Point;
class Line;
class Wireframe;
class BezierCurve;

class AbstractClipper {
public:
    virtual ~AbstractClipper() {}
    virtual void clip_to_area(Point &p) = 0;
    virtual void clip_to_area(Line &line) = 0;
    virtual void clip_to_area(Wireframe &wf) = 0;
    virtual void clip_to_area(BezierCurve &bc) = 0;
    virtual void set_line_clipping_method(LineClipping type) = 0;
    virtual void set_polygon_clipping_method(PolygonClipping type) = 0;
};

#endif  // ABSTRACT_CLIPPER_HPP