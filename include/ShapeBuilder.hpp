// ShapeBuilder.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange
//
// This class should be used for creating objects of type Shape.
// It has a static method called instance(), which should be called
// to get a pointer to this class and operate on its members.

#ifndef SHAPE_BUILDER_HPP
#define SHAPE_BUILDER_HPP

#include <list>
#include <string>
#include "ShapeType.h"

class Shape;
class Point;

class ShapeBuilder {

private:
    static ShapeBuilder *m_pInstance;
    std::list<Point*> m_points;
    std::string m_name;

private:
    ShapeBuilder() {}
    ~ShapeBuilder();
    ShapeBuilder(const ShapeBuilder &) {};
    void operator=(const ShapeBuilder &) {};
    void reset();
    Point* createPoint();

public:
    static ShapeBuilder* instance();
    void addName(const std::string &);
    void addPoint(const double, const double);
    void addPoint(const std::string &, const double, const double);
    void rollback();
    Shape* createShape(ShapeType);
};

#endif  // SHAPE_BUILDER_HPP