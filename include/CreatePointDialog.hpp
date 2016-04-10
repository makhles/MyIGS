// CreatePointDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_POINT_DIALOG_H
#define CREATE_POINT_DIALOG_H

#include <gtkmm/dialog.h>

namespace Gtk {
    class Label;
    class Entry;
}

class CreatePointDialog : public Gtk::Dialog
{
private:

    // Attribute
    Gtk::Label * const m_nameLabel;
    Gtk::Label * const m_xLabel;
    Gtk::Label * const m_yLabel;
    Gtk::Entry * const m_nameEntry;
    Gtk::Entry * const m_xEntry;
    Gtk::Entry * const m_yEntry;

    // Signal handler
    void on_my_response(int response_id);

public:

    // Life cycle
    CreatePointDialog(const Glib::ustring &title);
    ~CreatePointDialog();
};

#endif  // CREATE_POINT_DIALOG_H