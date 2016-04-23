// CreateWireframeDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_WIREFRAME_DIALOG_HPP
#define CREATE_WIREFRAME_DIALOG_HPP

#include <gtkmm.h>

// Forward declarations
class CoordBox;

class CreateWireframeDialog : public Gtk::Dialog {
private:
    bool m_filled;
    bool m_minVertices;
    CoordBox * const m_coordBox;
    Gtk::Label * const m_nameLabel;
    Gtk::Entry * const m_nameEntry;

    // Signal handler
    void on_my_response(int response_id);
    void create_shape();
    void add_point();
    void on_filled_button_toggled();

public:
    CreateWireframeDialog(const Glib::ustring &title);
    ~CreateWireframeDialog() {}
    bool minimum_vertices() const { return m_minVertices; }
};

#endif  // CREATE_WIREFRAME_DIALOG_HPP