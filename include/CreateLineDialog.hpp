// CreateLineDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_LINE_DIALOG_HPP
#define CREATE_LINE_DIALOG_HPP

#include <gtkmm/dialog.h>

namespace Gtk {
    class Label;
    class Entry;
}

class CreateLineDialog : public Gtk::Dialog {
private:
    // Attribute
    Gtk::Label * const m_nameLabel;
    Gtk::Label * const m_x1Label;
    Gtk::Label * const m_x2Label;
    Gtk::Label * const m_y1Label;
    Gtk::Label * const m_y2Label;
    Gtk::Label * const m_z1Label;
    Gtk::Label * const m_z2Label;
    Gtk::Entry * const m_nameEntry;
    Gtk::Entry * const m_x1Entry;
    Gtk::Entry * const m_x2Entry;
    Gtk::Entry * const m_y1Entry;
    Gtk::Entry * const m_y2Entry;
    Gtk::Entry * const m_z1Entry;
    Gtk::Entry * const m_z2Entry;

    // Signal handler
    void on_my_response(int response_id);

public:
    // Life cycle
    CreateLineDialog(const Glib::ustring &title);
    ~CreateLineDialog() {}
};

#endif  // CREATE_LINE_DIALOG_HPP