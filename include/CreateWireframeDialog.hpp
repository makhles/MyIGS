// CreateWireframeDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_WIREFRAME_DIALOG_HPP
#define CREATE_WIREFRAME_DIALOG_HPP

#include <gtkmm.h>
// #include <list>

// Forward declarations
class CoordBox;

class CreateWireframeDialog : public Gtk::Dialog {
private:
    // Attribute
    // int m_totalPoints;
    bool m_filled;
    bool m_minVertices;
    // Gtk::VBox * const m_coordBox;
    CoordBox * const m_coordBox;
    Gtk::Label * const m_nameLabel;
    Gtk::Entry * const m_nameEntry;
    // std::list<Gtk::Entry*> m_coordEntries;

    // Signal handler
    void on_my_response(int response_id);
    void create_shape();
    void add_point();
    void on_filled_button_toggled();

public:
    // Life cycle
    CreateWireframeDialog(const Glib::ustring &title);
    ~CreateWireframeDialog() {}
    // bool build_wireframe() const { return m_totalPoints >= 3; }
    bool minimum_vertices() const { return m_minVertices; }
};

#endif  // CREATE_WIREFRAME_DIALOG_HPP