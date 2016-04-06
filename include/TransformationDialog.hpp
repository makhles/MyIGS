// TransformationDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSFORMATION_DIALOG_HPP
#define TRANSFORMATION_DIALOG_HPP

#include "gtkmm.h"

class TransformationDialog : public Gtk::Dialog {

protected:

    Gtk::ListViewText * const m_transformations;

    // Translation
    Gtk::Entry * const m_dxEntry;
    Gtk::Entry * const m_dyEntry;

    // // Rotation
    // Gtk::Label * const m_angleLabel;  // Angle about the z axis
    // Gtk::Entry * const m_angleEntry;
    // Gtk::Label * const m_xLabel;      // Reference point x coordinate for rotation
    // Gtk::Label * const m_yLabel;      // Reference point y coordinate for rotation
    // Gtk::Entry * const m_xEntry;
    // Gtk::Entry * const m_yEntry;

    // // Scaling
    // Gtk::Label * const m_sxLabel;
    // Gtk::Label * const m_syLabel;
    // Gtk::Entry * const m_sxEntry;
    // Gtk::Entry * const m_syEntry;

    void applyTransformations();

    // Signal handlers
    void on_add_button_clicked();
    void on_rem_button_clicked();
    void on_my_response(int response_id);
    void on_notebook_switch_page(Gtk::Widget* page, guint page_number);

public:
    TransformationDialog(const Glib::ustring &title);
    virtual ~TransformationDialog() {}

};

#endif  // TRANSFORMATION_DIALOG_HPP