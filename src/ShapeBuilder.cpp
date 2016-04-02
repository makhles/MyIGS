// ShapeBuilder.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include "ShapeBuilder.hpp"
#include "Point.h"
#include "DeleteList.hpp"

// Global static pointer to ensure a single instance of the class.
ShapeBuilder * ShapeBuilder::m_pInstance = nullptr;

ShapeBuilder* ShapeBuilder::instance() {
    if (!m_pInstance) {
        m_pInstance = new ShapeBuilder;
    }
    return m_pInstance;
}

void ShapeBuilder::addPoint(const double x, const double y) {
    Point *p = new Point("", x, y);
    m_points.push_back(p);
}

void ShapeBuilder::clearPoints() {
    if (!m_points.empty()) {
        std::for_each (m_points.begin(),
                       m_points.end(),
                       DeleteList<Point*>());
        m_points.clear();
    }
}