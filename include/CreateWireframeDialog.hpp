// CreateWireframeDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_WIREFRAME_DIALOG_HPP
#define CREATE_WIREFRAME_DIALOG_HPP

#include <gtkmm/dialog.h>
#include <list>

namespace Gtk {
    class Label;
    class Entry;
}

class CreateWireframeDialog : public Gtk::Dialog
{
private:

    // Attribute
    Gtk::Label * const _nameLabel;
    Gtk::Entry * const _nameEntry;
    std::list<Gtk::Entry*> m_coordEntries;

    void addCoord();

    // Signal handler
    void on_button_add_clicked();
    void on_my_response(int response_id);

public:

    // Life cycle
    CreateWireframeDialog(const Glib::ustring &title);
    ~CreateWireframeDialog() {}
};

#endif  // CREATE_WIREFRAME_DIALOG_HPP