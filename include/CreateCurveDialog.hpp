// CreateCurveDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#ifndef CREATE_CURVE_DIALOG_HPP
#define CREATE_CURVE_DIALOG_HPP

#include <gtkmm.h>
#include "ShapeType.hpp"

// Forward declarations
class CoordBox;

class CreateCurveDialog : public Gtk::Dialog {
private:
    bool m_minVertices;
    Gtk::Notebook * const m_notebook;  // The tabbed pane
    CoordBox * const m_bezier_CoordBox;
    CoordBox * const m_bspline_CoordBox;
    Gtk::Label * const m_nameLabel;
    Gtk::Entry * const m_nameEntry;

    void show_unfilled_entries_dialog(const std::string &secondary_message);

    // Signal handler
    void on_my_response(int response_id);
    void create_shape();
    void on_page_switch(Widget* page, guint page_number);
    void on_add_bezier_curve_button_clicked();
    void on_add_bspline_point_button_clicked();

public:
    CreateCurveDialog(const Glib::ustring &title);
    ~CreateCurveDialog() {}
    bool minimum_vertices() const { return m_minVertices; }
    ShapeType selected_curve_type() const;
};

#endif  // CREATE_CURVE_DIALOG_HPP