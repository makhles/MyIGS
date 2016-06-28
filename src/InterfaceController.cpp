// InterfaceController.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

// For debugging, uncomment the following define
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

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
#include "ObjReader.hpp"
#include "WindowClipper.hpp"


typedef std::vector<Coord<double>*> DCoordVector;

/* ============================================================================================= */
InterfaceController::InterfaceController(MyIGS *interface, Canvas *viewport) :
/* ============================================================================================= */
    m_interface(interface),
    m_viewport(viewport),
    m_writer(nullptr),
    m_clipper(new WindowClipper())
{
    m_viewport->set_controller(this);
    this->update_gtm();
}

/* ============================================================================================= */
InterfaceController::~InterfaceController()
/* ============================================================================================= */
{
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        delete *shape;
        shape++;
    }
    m_shapes.clear();
    delete m_clipper;
}

/* ============================================================================================= */
void InterfaceController::create_shape(ShapeType type)
/* ============================================================================================= */
{
    // Create a new shape based on its type.
    Shape *shape = ShapeBuilder::instance()->create_shape(type);
    this->add(shape);
    this->update(shape);
    m_viewport->invalidate();
}

/* ============================================================================================= */
void InterfaceController::add(Shape *shape)
/* ============================================================================================= */
{
    m_shapes.push_back(shape);
    m_interface->append_object(shape->name());
}

/* ============================================================================================= */
void InterfaceController::update(Shape *shape)
/* ============================================================================================= */
{
    shape->normalize(m_gtm);
    shape->clip_to_window(*m_clipper);
    this->to_viewport(shape);
}

/* ============================================================================================= */
void InterfaceController::update_gtm()
/* ============================================================================================= */
{
    // Global Transformation Matrix
    TMatrixBuilder::instance()->normalizing_matrix(m_gtm, m_window.center(),
            m_window.scaling(), m_window.orientation());

    DEBUG_MSG("--------------------------------------");
    DEBUG_MSG("GTM:");
    DEBUG_MSG(m_gtm(0,0) << "  " << m_gtm(0,1) << "  " << m_gtm(0,2) << "  " << m_gtm(0,3));
    DEBUG_MSG(m_gtm(1,0) << "  " << m_gtm(1,1) << "  " << m_gtm(1,2) << "  " << m_gtm(1,3));
    DEBUG_MSG(m_gtm(2,0) << "  " << m_gtm(2,1) << "  " << m_gtm(2,2) << "  " << m_gtm(2,3));
    DEBUG_MSG(m_gtm(3,0) << "  " << m_gtm(3,1) << "  " << m_gtm(3,2) << "  " << m_gtm(3,3));
    DEBUG_MSG("--------------------------------------");
}

/* ============================================================================================= */
void InterfaceController::update_shapes()
/* ============================================================================================= */
{
    // Called whenever the Window is translated, scaled or rotated.
    this->update_gtm();
    DEBUG_MSG("m_shapes.size = " << m_shapes.size());
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->normalize(m_gtm);
        (*shape)->clip_to_window(*m_clipper);
        this->to_viewport(*shape);
        shape++;
    }
    m_viewport->invalidate();
}

/* ============================================================================================= */
void InterfaceController::draw_shapes(ShapeDrawer &drawer)
/* ============================================================================================= */
{
    auto shape = m_shapes.begin();
    while (shape != m_shapes.end()) {
        (*shape)->accept(&drawer);
        shape++;
    }
}

/* ============================================================================================= */
void InterfaceController::to_viewport(Shape *shape)
/* ============================================================================================= */
{
    DEBUG_MSG("Converting to viewport coordinates.");

    shape->clear_viewport_coordinates();
    const DCoordVector& coords = shape->normalized_coords();

    if (!coords.empty()) {
        int xvp, yvp;
        double xratio, yratio;
        double xvp_min, yvp_max;
        double xnc, ync;

        auto c = coords.begin();
        while (c != coords.end()) {
            // Parameters
            xratio = m_viewport->vp_width() / 2.0;
            yratio = m_viewport->vp_height() / 2.0;
            xvp_min = m_viewport->xvp_min();
            yvp_max = m_viewport->yvp_max();
            xnc = (*c)->x();
            ync = (*c)->y();

            DEBUG_MSG("-----------------------------");
            DEBUG_MSG("xnc = " << xnc);
            DEBUG_MSG("ync = " << ync);

            // Viewport coordinates
            xvp = (int) (xvp_min + xratio * (xnc + 1.0));
            yvp = (int) (yvp_max - yratio * (ync + 1.0));

            // Update shape
            shape->add_viewport_coordinate(new Coord<int>(xvp, yvp));
            c++;

            DEBUG_MSG("xvp = " << xvp);
            DEBUG_MSG("yvp = " << yvp);
            DEBUG_MSG("-----------------------------");
        }
    }
}

/* ============================================================================================= */
void InterfaceController::translate_window(int rightOrLeft, int upOrDown, int backOrForth)
/* ============================================================================================= */
{
    TMatrix m(4);
    double dx = rightOrLeft * DEVICE_DISPLACEMENT * m_window.width() / m_viewport->vp_width();
    double dy = upOrDown * DEVICE_DISPLACEMENT * m_window.height() / m_viewport->vp_height();
    double dz = backOrForth * DEVICE_DISPLACEMENT;
    TMatrixBuilder::instance()->window_translation(m, m_window.center(), m_window.orientation(),
            Coord<double>(dx, dy, dz));
    std::vector<double> window_center, res;
    window_center.push_back(m_window.center().x());
    window_center.push_back(m_window.center().y());
    window_center.push_back(m_window.center().z());
    m.multiply_by_vector(window_center, res);
    m_window.translate(res);
    this->update_shapes();
}

/* ============================================================================================= */
void InterfaceController::scale_window(double factor)
/* ============================================================================================= */
{
    m_window.scale(factor);
    this->update_shapes();
}

/* ============================================================================================= */
void InterfaceController::rotate_window(const Coord<double> &angles)
/* ============================================================================================= */
{
    m_window.rotate(angles);
    this->update_shapes();
}

/* ============================================================================================= */
Shape* InterfaceController::find_shape(const std::string &obj)
/* ============================================================================================= */
{
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

/* ============================================================================================= */
void InterfaceController::translate(const TransformationDialog &dialog)
/* ============================================================================================= */
{
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrix trans_mtx(4);
        Coord<double> translation = dialog.translation_coord();
        TMatrixBuilder::instance()->translation_matrix(trans_mtx, translation);
        shape->transform(trans_mtx);
        this->update(shape);
        m_viewport->invalidate();
    } else {
        DEBUG_MSG("Couldn't find specified object!");
    }
}

/* ============================================================================================= */
void InterfaceController::scale(const TransformationDialog &dialog)
/* ============================================================================================= */
{
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrix scale_mtx(4);
        Coord<double> scaling = dialog.scaling_coord();
        Coord<double> centroid = shape->get_centroid();
        TMatrixBuilder::instance()->scaling_matrix(scale_mtx, scaling, centroid);
        shape->transform(scale_mtx);
        this->update(shape);
        m_viewport->invalidate();
    } else {
        DEBUG_MSG("Couldn't find specified object!");
    }
}

/* ============================================================================================= */
void InterfaceController::rotate(const TransformationDialog &dialog)
/* ============================================================================================= */
{
    std::string obj_name = dialog.get_selected_object();
    Shape *shape = this->find_shape(obj_name);
    if (shape) {
        TMatrix rot_mtx(4);
        double angle = dialog.get_angle();
        Coord<double> point_a = dialog.rotation_coord_a();
        Coord<double> point_b = dialog.rotation_coord_b();
        TMatrixBuilder::instance()->rotation_matrix(rot_mtx, angle, point_a, point_b);
        shape->transform(rot_mtx);
        this->update(shape);
        m_viewport->invalidate();
    } else {
        DEBUG_MSG("Couldn't find specified object!");
    }
}

/* ====================================================xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx========================================= */
void InterfaceController::export_obj_file()
/* ============================================================================================= */
{
    DEBUG_MSG("Exporting shapes to Wavefront .obj file");
    if (m_shapes.empty()) {
        DEBUG_MSG(" nothing to export.");
    } else {
        m_writer = new ObjWriter();
        auto shape = m_shapes.begin();
        while (shape != m_shapes.end()) {
            (*shape)->write_to_file(m_writer);
            shape++;
        }
        m_writer->write_to_file();
        DEBUG_MSG(" done.");
        delete m_writer;
        m_writer = nullptr;
    }
}

/* ============================================================================================= */
bool InterfaceController::import_obj_files(std::vector<std::string> &filenames)
/* ============================================================================================= */
{
    ObjReader reader;
    std::vector<Shape*> shapes;
    bool read_ok = reader.read_shapes(shapes, filenames);
    if (read_ok) {
        for (Shape *s : shapes) {
            this->add(s);
            this->update(s);
        }
        DEBUG_MSG("... " << shapes.size() << " shapes were added successfully!");
    }
    m_status_msg = reader.get_status_msg();
    return read_ok;
}

/* ============================================================================================= */
void InterfaceController::set_line_clipping_method(LineClipping type)
/* ============================================================================================= */
{
    m_clipper->set_line_clipping_method(type);
}

/* ============================================================================================= */
void InterfaceController::set_polygon_clipping_method(PolygonClipping type)
/* ============================================================================================= */
{
    m_clipper->set_polygon_clipping_method(type);
}

