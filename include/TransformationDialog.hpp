// TransformationDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSFORMATION_DIALOG_HPP
#define TRANSFORMATION_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <gtkmm/notebook.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

class TransformationDialog : public Gtk::Dialog {

protected:

    Gtk::Notebook * const m_notebook;  // The tabbed pane

    Gtk::Entry * const m_dxEntry;     // Translation in x
    Gtk::Entry * const m_dyEntry;     // Translation in y
    Gtk::Entry * const m_sxEntry;     // Scalilng in x
    Gtk::Entry * const m_syEntry;     // Scalilng in y
    Gtk::Entry * const m_xEntry;      // Reference point x-coord for rotation
    Gtk::Entry * const m_yEntry;      // Reference point x-coord for rotation
    Gtk::Entry * const m_angleEntry;  // Angle of rotation about the Z axis
    Gtk::Label * const m_xLabel;      // X-coord label for rotation
    Gtk::Label * const m_yLabel;      // Y-coord label for rotation

    bool m_origin_rbutton;
    bool m_point_rbutton;
    bool m_centroid_rbutton;

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
    TransformationDialog(const Glib::ustring &title);
    virtual ~TransformationDialog() {}

};

#endif  // TRANSFORMATION_DIALOG_HPP