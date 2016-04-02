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
    Gtk::Label * const _nameLabel;
    Gtk::Label * const _xLabel;
    Gtk::Label * const _yLabel;
    Gtk::Entry * const _nameEntry;
    Gtk::Entry * const _xEntry;
    Gtk::Entry * const _yEntry;

    // Signal handler
    void on_my_response(int response_id);

public:

    // Life cycle
    CreatePointDialog(const Glib::ustring &title);
    ~CreatePointDialog();
};

#endif  // CREATE_POINT_DIALOG_H