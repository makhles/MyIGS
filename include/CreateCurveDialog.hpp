// CreateCurveDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_CURVE_DIALOG_HPP
#define CREATE_CURVE_DIALOG_HPP

#include <gtkmm.h>

// Forward declarations
class CoordBox;

class CreateCurveDialog : public Gtk::Dialog {
private:
    bool m_minVertices;
    CoordBox * const m_coordBox;
    Gtk::Label * const m_nameLabel;
    Gtk::Entry * const m_nameEntry;

    // Signal handler
    void on_my_response(int response_id);
    void create_shape();
    void add_point();

public:
    CreateCurveDialog(const Glib::ustring &title);
    ~CreateCurveDialog() {}
    bool minimum_vertices() const { return m_minVertices; }
};

#endif  // CREATE_CURVE_DIALOG_HPP