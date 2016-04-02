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
    int m_totalPoints;
    Gtk::Label * const m_nameLabel;
    Gtk::Entry * const m_nameEntry;
    std::list<Gtk::Entry*> m_coordEntries;

    // Signal handler
    void on_my_response(int response_id);
    void addPoint();
    void createShape();

public:

    // Life cycle
    CreateWireframeDialog(const Glib::ustring &title);
    ~CreateWireframeDialog() {}
    bool buildWireframe() const { return m_totalPoints >= 3;}
};

#endif  // CREATE_WIREFRAME_DIALOG_HPP