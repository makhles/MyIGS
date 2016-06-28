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
class CoordBox;


class TransformationDialog : public Gtk::Dialog {

protected:
    InterfaceController * const m_controller;
    ObjectsTreeView * const m_objTreeView;
    Gtk::Notebook * const m_notebook;  // The tabbed pane

    Gtk::Entry * const m_dxEntry;  // Translation in x
    Gtk::Entry * const m_dyEntry;  // Translation in y
    Gtk::Entry * const m_dzEntry;  // Translation in z

    Gtk::Entry * const m_sxEntry;  // Scaling in x
    Gtk::Entry * const m_syEntry;  // Scaling in y
    Gtk::Entry * const m_szEntry;  // Scaling in z

    Gtk::Entry * const m_axEntry;  // Rotation axis first point x coord
    Gtk::Entry * const m_ayEntry;  // Rotation axis first point y coord
    Gtk::Entry * const m_azEntry;  // Rotation axis first point z coord
    Gtk::Entry * const m_bxEntry;  // Rotation axis second point x coord
    Gtk::Entry * const m_byEntry;  // Rotation axis second point y coord
    Gtk::Entry * const m_bzEntry;  // Rotation axis second point z coord

    Gtk::Entry * const m_angleEntry;  // Angle of rotation about the Z axis
    CoordBox * const m_coordBox;

    bool m_own_axis_rb;
    bool m_rnd_axis_rb;

    double m_dx;     // Translation in x
    double m_dy;     // Translation in y
    double m_dz;     // Translation in z
    double m_sx;     // Scaling in x
    double m_sy;     // Scaling in y
    double m_sz;     // Scaling in z
    double m_angle;  // Rotation angle
    double m_rax;    // Reference point A x-coord
    double m_ray;    // Reference point A y-coord
    double m_raz;    // Reference point A z-coord
    double m_rbx;    // Reference point B x-coord
    double m_rby;    // Reference point B y-coord
    double m_rbz;    // Reference point B z-coord

    bool transform();
    bool translate();
    bool scale();
    bool rotate();

    // Signal handlers
    void handle_own_axis_rbutton_toggled();
    void handle_rnd_axis_rbutton_toggled();
    void show_rnd_axis();
    void hide_rnd_axis();
    void on_my_response(int response_id);

public:
    TransformationDialog(const Glib::ustring&, InterfaceController*, ObjectsTreeView *);
    virtual ~TransformationDialog() {}

    // Getters
    Coord<double> translation_coord() const { return Coord<double>(m_dx, m_dy, m_dz); }
    Coord<double> scaling_coord() const { return Coord<double>(m_sx, m_sy, m_sz); }
    Coord<double> rotation_coord_a() const { return Coord<double>(m_rax, m_ray, m_raz); }
    Coord<double> rotation_coord_b() const { return Coord<double>(m_rbx, m_rby, m_rbz); }
    double get_angle() const {return m_angle;}
    std::string get_selected_object() const;
};

#endif  // TRANSFORMATION_DIALOG_HPP