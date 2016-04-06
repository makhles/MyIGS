// TransformationDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef TRANSFORMATION_DIALOG_HPP
#define TRANSFORMATION_DIALOG_HPP

#include "gtkmm.h"
#include "TransformationType.hpp"

class TransformationDialog : public Gtk::Dialog {

protected:

    Gtk::ListViewText * const m_transformations;

    Gtk::Entry * const m_dxEntry;  // Translation in x
    Gtk::Entry * const m_dyEntry;  // Translation in y
    Gtk::Entry * const m_sxEntry;  // Scalilng in x
    Gtk::Entry * const m_syEntry;  // Scalilng in y

    // // Rotation
    // Gtk::Entry * const m_angleEntry;
    // Gtk::Entry * const m_xEntry;
    // Gtk::Entry * const m_yEntry;

    TransformationType m_transformType;
    unsigned m_translationsCount;
    unsigned m_scalingCount;

    void addTranslation();
    void addScaling();
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