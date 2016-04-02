// CreateLineDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_LINE_DIALOG_H
#define CREATE_LINE_DIALOG_H

#include <gtkmm/dialog.h>

namespace Gtk {
    class Label;
    class Entry;
}

class CreateLineDialog : public Gtk::Dialog
{
private:

    // Attribute
    Gtk::Label * const _nameLabel;
    Gtk::Label * const _x1Label;
    Gtk::Label * const _x2Label;
    Gtk::Label * const _y1Label;
    Gtk::Label * const _y2Label;
    Gtk::Entry * const _nameEntry;
    Gtk::Entry * const _x1Entry;
    Gtk::Entry * const _x2Entry;
    Gtk::Entry * const _y1Entry;
    Gtk::Entry * const _y2Entry;

    // Signal handler
    void on_my_response(int response_id);

public:

    // Life cycle
    CreateLineDialog(const Glib::ustring &title);
    ~CreateLineDialog() {}
};

#endif  // CREATE_LINE_DIALOG_H