// AbstractDrawer.hpp
// Authors: Leonardo Vailatti
//          Makhles R. Lange

#ifndef ABSTRACT_DRAWER_HPP
#define ABSTRACT_DRAWER_HPP

class Point;
class Line;
class Wireframe;
class BezierCurve;

class AbstractDrawer {
public:
    virtual void draw(Point &point) = 0;
    virtual void draw(Line &line) = 0;
    virtual void draw(Wireframe &wireframe) = 0;
    virtual void draw(BezierCurve &bc) = 0;
};

#endif  // ABSTRACT_DRAWER_HPP