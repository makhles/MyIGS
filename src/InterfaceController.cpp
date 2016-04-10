// InterfaceController.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "InterfaceController.hpp"
#include "MyIGS.hpp"
#include "Canvas.hpp"
#include "TransformationDialog.hpp"
#include "ShapeBuilder.hpp"
#include "ShapeDrawer.hpp"
#include "Point.hpp"
#include "Line.hpp"
#include "Wireframe.hpp"
#include "Coord.hpp"
#include "TMatrix.hpp"
#include "TMatrixBuilder.hpp"


InterfaceController::InterfaceController(MyIGS *interface, Canvas *canvas) :
    m_interface(interface),
    m_canvas(canvas),
    m_xViewportMin(0),
    m_xViewportMax(500),
    m_yViewportMin(0),
    m_yViewportMax(500)
{
    m_canvas->set_controller(this);
    m_windowHandler.set_viewport(m_canvas);
}


InterfaceController::~InterfaceController() {
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        delete *shape;
        shape++;
    }
    m_shapes.clear();
}


// Create a new shape based on its type.
void InterfaceController::create_shape(ShapeType type) {
    Shape *shape = ShapeBuilder::instance()->create_shape(type);
    this->finalize_shape(shape);
}


void InterfaceController::finalize_shape(Shape *shape) {
    m_shapes.push_back(shape);
    m_interface->append_object(shape->get_name());
    this->update(shape);
}


void InterfaceController::translate(const TransformationDialog &dialog) {
    double dx = dialog.get_dx();
    double dy = dialog.get_dy();
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrixBuilder::instance()->translation_matrix(m_gtm, dx, dy);
        shape->transform(&m_gtm);
        this->update(shape);
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


void InterfaceController::scale(const TransformationDialog &dialog) {
    double sx = dialog.get_sx();
    double sy = dialog.get_sy();
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        const Coord<double> c = shape->get_centroid();
        TMatrixBuilder::instance()->scaling_matrix(m_gtm, sx, sy, c.x(), c.y());
        shape->transform(&m_gtm);
        this->update(shape);
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


// Apply a rotation about the origin or some arbitrary point
void InterfaceController::rotate(const TransformationDialog &dialog) {
    double angle = dialog.get_angle();
    double x = dialog.get_refX();
    double y = dialog.get_refY();
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrixBuilder::instance()->rotation_matrix(m_gtm, angle, x, y);
        shape->transform(&m_gtm);
        this->update(shape);
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


void InterfaceController::rotate_about_centroid(const TransformationDialog &dialog) {
    double angle = dialog.get_angle();
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        const Coord<double> c = shape->get_centroid();
        TMatrixBuilder::instance()->rotation_matrix(m_gtm, angle, c.x(), c.y());
        shape->transform(&m_gtm);
        this->update(shape);
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


void InterfaceController::update(Shape *shape) {
    shape->clip_to_window(&m_window);
    // this->toViewport(shape);
    m_canvas->invalidate();
}


// Called whenever the Window is translated or rotated.
void InterfaceController::update_shapes() {
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        this->update((*shape));
        shape++;
    }
}


void InterfaceController::draw_shapes(ShapeDrawer &drawer) {
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->accept(&drawer);
        shape++;
    }
}


// void InterfaceController::toViewport(Shape *shape) {
//     std::cout << "Converting to viewport coordinates." << std::endl;

//     const std::list<Coord<double>*>* wCoords = shape->getWindowCoordinates();
//     shape->clearViewportCoordinates();

//     int vpX, vpY;
//     auto c = wCoords->begin();
//     while (c != wCoords->end()) {
//         vpX = this->xWindowToViewport((*c)->x());
//         vpY = this->yWindowToViewport((*c)->y());
//         shape->addViewportCoordinate(new Coord<int>(vpX, vpY));
//         c++;
//         std::cout << "vpX = " << vpX << std::endl;
//         std::cout << "vpY = " << vpY << std::endl;
//     }
// }


// int InterfaceController::xWindowToViewport(const double xWindow) {
//     double xViewport;
//     xViewport = xWindow - m_window.getXMin();
//     xViewport *= (m_xViewportMax - m_xViewportMin)/(m_window.getXMax() - m_window.getXMin());
//     xViewport += m_xViewportMin;
//     return (int) xViewport;
// }


// int InterfaceController::yWindowToViewport(const double yWindow) {
//     double yViewport;
//     yViewport = (m_yViewportMax - m_yViewportMin) / (m_window.getYMax() - m_window.getYMin());
//     yViewport *= (yWindow - m_window.getYMin());
//     yViewport = m_yViewportMax - yViewport;
//     return (int) yViewport;
// }


void InterfaceController::move_window(int moveX, int moveY) {
    m_windowHandler.translate_window(moveX, moveY);
    this->update_shapes();
}


void InterfaceController::scale_window(double factor) {
    m_windowHandler.scale_window(factor);
    this->update_shapes();
}


void InterfaceController::rotate_window(double angle) {
    m_windowHandler.rotate_window(angle);
    this->update_shapes();
}


Shape* InterfaceController::find_shape(const std::string &obj) {
    Shape *shapeToReturn = nullptr;
    auto shape = m_shapes.cbegin();
    while (shape != m_shapes.cend()) {
        if ((*shape)->get_name() == obj) {
            shapeToReturn = *shape;
        }
        shape++;
    }
    return shapeToReturn;
}