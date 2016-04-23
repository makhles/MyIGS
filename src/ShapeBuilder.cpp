// ShapeBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "ShapeBuilder.hpp"
#include "Shape.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "DeleteList.hpp"

// Global static pointer to ensure a single instance of the class.
ShapeBuilder * ShapeBuilder::m_pInstance = nullptr;


ShapeBuilder* ShapeBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new ShapeBuilder();
    }
    return m_pInstance;
}


void ShapeBuilder::add_name(const std::string &name) {
    m_name = name;
}


// Called when the Shape is made up of several Points.
void ShapeBuilder::add_point(const double x, const double y) {
    if (m_name.empty()) {
        m_name = "Nameless";
    }
    int pNumber = m_points.size();
    std::string pName = m_name + "_p" + std::to_string(pNumber);
    Point *p = new Point(pName, x, y);
    m_points.push_back(p);
}


// Called when the Shape is just a Point.
void ShapeBuilder::add_point(const std::string &name, const double x, const double y) {
    Point *p = new Point(name, x, y);
    m_points.push_back(p);
}

// Create a new shape based on the value of type parameter.
Shape* ShapeBuilder::create_shape(ShapeType type) {
    Shape *shape;
    switch (type) {
        case ShapeType::POINT:
        {
            shape = ShapeBuilder::create_point();
            break;
        }
        case ShapeType::LINE:
        {
            shape = ShapeBuilder::create_line();
            break;
        }
        case ShapeType::WIREFRAME:
        {
            shape = ShapeBuilder::create_wireframe();
            break;
        }
        case ShapeType::BEZIER_CUBIC:
        {
            //shape = ShapeBuilder::create_bezier_curve();
            break;
        }
    }
    ShapeBuilder::reset();
    return shape;
}


Point* ShapeBuilder::create_point() {
    Point *p = m_points.front();
    m_points.pop_front();
    return p;
}


Line* ShapeBuilder::create_line() {
    Point *p1 = m_points.front();
    m_points.pop_front();
    Point *p2 = m_points.front();
    m_points.pop_front();
    return new Line(m_name, p1, p2);
}


Wireframe* ShapeBuilder::create_wireframe() {
    Wireframe *wireframe = new Wireframe(m_name, m_filled);
    auto p = m_points.begin();
    while (p != m_points.end()) {
        wireframe->add_point((*p));
        p++;
    }
    return wireframe;
}


// Reset all members for creating another shape.
// Only called if previous shape was successfully built,
// so there are some pointers that need to be removed from
// the list but not deleted.
void ShapeBuilder::reset() {
    m_points.clear();
    m_name = "";
}


ShapeBuilder::~ShapeBuilder() {
    ShapeBuilder::rollback();
}


// In case there are any dangling pointers after
// the user has cancelled the shape creation process.
void ShapeBuilder::rollback() {
    if (!m_points.empty()) {
        std::for_each (m_points.begin(),
                       m_points.end(),
                       DeleteList<Point*>());
        ShapeBuilder::reset();
    }
}