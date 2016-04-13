// InterfaceController.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <fstream>
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
#include "Writer.hpp"
#include "ObjWriter.hpp"


typedef std::list<Coord<double>*> DCoordList;


InterfaceController::InterfaceController(MyIGS *interface, Canvas *viewport) :
    m_interface(interface),
    m_viewport(viewport)
{
    m_viewport->set_controller(this);
}


InterfaceController::~InterfaceController() {
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        delete *shape;
        shape++;
    }
    m_shapes.clear();

    // Object writer
    if (m_writer) {
        delete m_writer;
    }
}


// Create a new shape based on its type.
void InterfaceController::create_shape(ShapeType type) {
    Shape *shape = ShapeBuilder::instance()->create_shape(type);
    this->finalize_shape(shape);
}


void InterfaceController::finalize_shape(Shape *shape) {
    m_shapes.push_back(shape);
    m_interface->append_object(shape->name());
    this->update(shape);
}


void InterfaceController::update(Shape *shape) {
    this->update_gtm();
    shape->normalize(m_gtm);
    shape->clip_to_window(m_window);
    this->to_viewport(shape);
    m_viewport->invalidate();
}


void InterfaceController::update_gtm() {
    double dx = - m_window.x_center();
    double dy = - m_window.y_center();
    double sx = 2.0 / m_window.width();
    double sy = 2.0 / m_window.height();
    double angle = - m_window.angle();

    std::cout << "------------------------------" << std::endl;
    std::cout << "Parameters for GTM:" << std::endl;
    std::cout << "dx...: " << dx << std::endl;
    std::cout << "dy...: " << dy << std::endl;
    std::cout << "sx...: " << sx << std::endl;
    std::cout << "sy...: " << sy << std::endl;
    std::cout << "angle: " << angle << std::endl;

    // Global Transformation Matrix
    TMatrixBuilder::instance()->normalizing_matrix(m_gtm, dx, dy, sx, sy, angle);

    std::cout << "------------------------------" << std::endl;
    std::cout << "GTM:" << std::endl;
    std::cout << m_gtm(0,0) << "  " << m_gtm(0,1) << "  " << m_gtm(0,2) << std::endl;
    std::cout << m_gtm(1,0) << "  " << m_gtm(1,1) << "  " << m_gtm(1,2) << std::endl;
    std::cout << m_gtm(2,0) << "  " << m_gtm(2,1) << "  " << m_gtm(2,2) << std::endl;
    std::cout << "------------------------------" << std::endl;
}



// Called whenever the Window is translated, scaled or rotated.
void InterfaceController::update_shapes() {
    this->update_gtm();
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->normalize(m_gtm);
        (*shape)->clip_to_window(m_window);
        this->to_viewport(*shape);
        shape++;
    }
    m_viewport->invalidate();
}


void InterfaceController::draw_shapes(ShapeDrawer &drawer) {
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->accept(&drawer);
        shape++;
    }
}



void InterfaceController::to_viewport(Shape *shape) {
    std::cout << "Converting to viewport coordinates." << std::endl;

    const DCoordList *ncList = shape->normalized_coordinates();
    shape->clear_viewport_coordinates();

    int xvp, yvp;
    double xratio, yratio;
    double xvp_min, yvp_max;
    double xnc, ync;

    auto c = ncList->begin();
    while (c != ncList->end()) {

        // Parameters
        xratio = m_viewport->vp_width() / 2.0;
        yratio = m_viewport->vp_height() / 2.0;
        xvp_min = m_viewport->xvp_min();
        yvp_max = m_viewport->yvp_max();
        xnc = (*c)->x();
        ync = (*c)->y();

        std::cout << "-----------------------------" << std::endl;
        std::cout << "xnc = " << xnc << std::endl;
        std::cout << "ync = " << ync << std::endl;

        // Viewport coordinates
        xvp = (int) (xvp_min + xratio * (xnc + 1.0));
        yvp = (int) (yvp_max - yratio * (ync + 1.0));

        // Update shape
        shape->add_viewport_coordinate(new Coord<int>(xvp, yvp));
        c++;

        std::cout << "xvp = " << xvp << std::endl;
        std::cout << "yvp = " << yvp << std::endl;
        std::cout << "-----------------------------" << std::endl;
    }
}


void InterfaceController::move_window(int rightOrLeft, int upOrDown) {
    double dx = DEVICE_DISPLACEMENT * m_window.width() / m_viewport->vp_width();
    double dy = DEVICE_DISPLACEMENT * m_window.height() / m_viewport->vp_height();
    m_window.translate(rightOrLeft * dx, upOrDown * dy);
    this->update_shapes();
}


void InterfaceController::scale_window(double factor) {
    m_window.scale(factor);
    this->update_shapes();
}


void InterfaceController::rotate_window(double angle) {
    m_window.rotate(-angle);  // The window and viewport rotate to opposing directions
    this->update_shapes();
}


Shape* InterfaceController::find_shape(const std::string &obj) {
    Shape *shapeToReturn = nullptr;
    auto shape = m_shapes.cbegin();
    while (shape != m_shapes.cend()) {
        if ((*shape)->name() == obj) {
            shapeToReturn = *shape;
        }
        shape++;
    }
    return shapeToReturn;
}


void InterfaceController::translate(const TransformationDialog &dialog) {
    double dx = dialog.get_dx();
    double dy = dialog.get_dy();
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrixBuilder::instance()->translation_matrix(m_gtm, dx, dy);
        shape->transform(m_gtm);
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
        shape->transform(m_gtm);
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
        shape->transform(m_gtm);
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
        shape->transform(m_gtm);
        this->update(shape);
    } else {
        std::cout << "Couldn't find specified object!" << std::endl;
    }
}


void InterfaceController::write_shapes_to_file() {
    m_writer = new ObjWriter();
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->write_to_file(m_writer);
        shape++;
    }
    m_writer->flush();
}