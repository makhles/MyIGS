// ShapeBuilder.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
//
// This class should be used for creating objects of type Shape.
// It has a static method called instance(), which should be called
// to get a pointer to this class and operate on its members.

#ifndef SHAPE_BUILDER_HPP
#define SHAPE_BUILDER_HPP

#include <vector>
#include <string>
#include "ShapeType.hpp"

class Shape;
class Point;
class Line;
class Wireframe;
class BezierCurve;

class ShapeBuilder {

private:
    static ShapeBuilder *m_pInstance;
    std::vector<Point*> m_points;
    std::string m_name;
    bool m_filled;

private:
    ShapeBuilder() {}
    ~ShapeBuilder();
    ShapeBuilder(const ShapeBuilder &) {};
    void operator=(const ShapeBuilder &) {};
    void reset();
    Point* create_point();
    Line* create_line();
    Wireframe* create_wireframe();
    BezierCurve* create_bezier_curve();

public:
    static ShapeBuilder* instance();
    void add_name(const std::string &);
    void set_filled(bool filled) { m_filled = filled; }
    void add_point(const double, const double);
    void add_point(const std::string &, const double, const double);
    void rollback();
    Shape* create_shape(ShapeType);
};

#endif  // SHAPE_BUILDER_HPP