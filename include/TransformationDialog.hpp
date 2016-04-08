// TransformationDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSFORMATION_DIALOG_HPP
#define TRANSFORMATION_DIALOG_HPP

#include "gtkmm.h"

class TransformationDialog : public Gtk::Dialog {

protected:

    Gtk::Notebook * const m_notebook;  // The tabbed pane

    Gtk::Entry * const m_dxEntry;  // Translation in x
    Gtk::Entry * const m_dyEntry;  // Translation in y
    Gtk::Entry * const m_sxEntry;  // Scalilng in x
    Gtk::Entry * const m_syEntry;  // Scalilng in y

    // Gtk::Entry * const m_angleEntry;
    // Gtk::Entry * const m_xEntry;
    // Gtk::Entry * const m_yEntry;

    bool transform();
    bool translate();
    bool scale();
    bool rotate();

    // Signal handlers
    void on_my_response(int response_id);

public:
    TransformationDialog(const Glib::ustring &title);
    virtual ~TransformationDialog() {}

};

#endif  // TRANSFORMATION_DIALOG_HPP