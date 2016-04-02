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

class Point;

class ShapeBuilder {
  public:
    static ShapeBuilder* instance();
    void addPoint(const double, const double);
    void clearPoints();

  private:
    ShapeBuilder() {};
    ShapeBuilder(ShapeBuilder const&) {};
    void operator=(ShapeBuilder const&) {};
    static ShapeBuilder *m_pInstance;
    std::list<Point*> m_points;
};

#endif  // SHAPE_BUILDER_HPP