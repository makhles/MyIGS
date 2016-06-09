// TransformationDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSFORMATION_DIALOG_HPP
#define TRANSFORMATION_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include "Coord.hpp"

// Forward declarations
class InterfaceController;
class ObjectsTreeView;


class TransformationDialog : public Gtk::Dialog {

protected:
    InterfaceController * const m_controller;
    ObjectsTreeView * const m_objTreeView;
    Gtk::Notebook * const m_notebook;  // The tabbed pane

    Gtk::Entry * const m_dxEntry;     // Translation in x
    Gtk::Entry * const m_dyEntry;     // Translation in y
    Gtk::Entry * const m_dzEntry;     // Translation in z
    Gtk::Entry * const m_sxEntry;     // Scaling in x
    Gtk::Entry * const m_syEntry;     // Scaling in y
    Gtk::Entry * const m_szEntry;     // Scaling in z
    Gtk::Entry * const m_xEntry;      // Reference point x-coord for rotation
    Gtk::Entry * const m_yEntry;      // Reference point x-coord for rotation
    Gtk::Entry * const m_angleEntry;  // Angle of rotation about the Z axis
    Gtk::Label * const m_xLabel;      // X-coord label for rotation
    Gtk::Label * const m_yLabel;      // Y-coord label for rotation

    bool m_origin_rbutton;
    bool m_point_rbutton;
    bool m_centroid_rbutton;

    double m_dx;     // Translation in x
    double m_dy;     // Translation in y
    double m_dz;     // Translation in z
    double m_sx;     // Scaling in x
    double m_sy;     // Scaling in y
    double m_sz;     // Scaling in z
    double m_angle;  // Rotation angle
    double m_refX;   // Reference point x-coord
    double m_refY;   // Reference point y-coord

    bool transform();
    bool translate();
    bool scale();
    bool rotate();

    // Signal handlers
    void handle_origin_rbutton_toggled();
    void handle_point_rbutton_toggled();
    void handle_centroid_rbutton_toggled();
    void show_reference_point();
    void hide_reference_point();
    void on_my_response(int response_id);

public:
    TransformationDialog(const Glib::ustring&, InterfaceController*, ObjectsTreeView *);
    virtual ~TransformationDialog() {}

    // Getters
    Coord<double> translation_coord() const { return Coord<double>(m_dx, m_dy, m_dz); }
    Coord<double> scaling_coord() const { return Coord<double>(m_sx, m_sy, m_sz); }
    double get_dx() const {return m_dx;}
    double get_dy() const {return m_dy;}
    double get_sx() const {return m_sx;}
    double get_sy() const {return m_sy;}
    double get_refX() const {return m_refX;}
    double get_refY() const {return m_refY;}
    double get_angle() const {return m_angle;}
    std::string get_selected_object() const;
};

#endif  // TRANSFORMATION_DIALOG_HPP