// CreateCurveDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <vector>
#include "CreateCurveDialog.hpp"
#include "ShapeBuilder.hpp"
#include "CoordBox.hpp"
#include "Coord.hpp"
#include "DeleteList.hpp"

// For debugging, uncomment the following define
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

#define CURVE_BEZIER_CUBIC 0
#define CURVE_BSPLINE 1

CreateCurveDialog::CreateCurveDialog(const Glib::ustring & title) :
    Dialog(title, true),
    m_minVertices(false),
    m_notebook(Gtk::manage(new Gtk::Notebook())),
    m_bezier_CoordBox(Gtk::manage(new CoordBox())),
    m_bspline_CoordBox(Gtk::manage(new CoordBox())),
    m_nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    m_nameEntry(Gtk::manage(new Gtk::Entry()))
{
    set_size_request(300, 300);
    set_resizable(false);
    set_border_width(10);

    // Entry for the name
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*m_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*m_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_spacing(0);
    name_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox, Gtk::PACK_SHRINK, 5);

    Gtk::Label * const bezier_label = Gtk::manage(new Gtk::Label("Bézier"));
    Gtk::Label * const bspline_label = Gtk::manage(new Gtk::Label("B-Spline"));

    Gtk::VBox * const bezier_vbox = Gtk::manage(new Gtk::VBox());
    Gtk::VBox * const bspline_vbox = Gtk::manage(new Gtk::VBox());

    bezier_vbox->set_size_request(200, -1);
    bspline_vbox->set_size_request(200, -1);

    // Add the pages to the tab pane
    m_notebook->append_page(*bezier_vbox, *bezier_label);
    m_notebook->append_page(*bspline_vbox, *bspline_label);
    m_notebook->signal_switch_page().connect(sigc::mem_fun(*this, &CreateCurveDialog::on_page_switch));

    Gtk::ScrolledWindow * const bezier_swindow = Gtk::manage(new Gtk::ScrolledWindow());
    Gtk::ScrolledWindow * const bspline_swindow = Gtk::manage(new Gtk::ScrolledWindow());

    bezier_swindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    bezier_swindow->set_size_request(-1, 200);
    bezier_swindow->set_border_width(5);
    bezier_swindow->add(*m_bezier_CoordBox);

    bspline_swindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    bspline_swindow->set_size_request(-1, 200);
    bspline_swindow->set_border_width(5);
    bspline_swindow->add(*m_bspline_CoordBox);

    Gtk::Button * const bezier_add_button = Gtk::manage(new Gtk::Button("Add curve"));
    Gtk::Button * const bspline_add_button = Gtk::manage(new Gtk::Button("Add point"));

    bezier_add_button->signal_clicked().connect(sigc::mem_fun(*this, &CreateCurveDialog::on_add_bezier_curve_button_clicked));
    bspline_add_button->signal_clicked().connect(sigc::mem_fun(*this, &CreateCurveDialog::on_add_bspline_point_button_clicked));

    bezier_vbox->pack_start(*bezier_swindow, Gtk::PACK_SHRINK, 0);
    bezier_vbox->pack_start(*bezier_add_button, Gtk::PACK_SHRINK, 0);
    bspline_vbox->pack_start(*bspline_swindow, Gtk::PACK_SHRINK, 0);
    bspline_vbox->pack_start(*bspline_add_button, Gtk::PACK_SHRINK, 0);

    get_content_area()->pack_start(*m_notebook, Gtk::PACK_SHRINK, 0);

    // Entries for the coordinates
    m_bezier_CoordBox->set_spacing(0);
    m_bspline_CoordBox->set_spacing(0);
    m_bezier_CoordBox->add_cubic_curve();
    m_bspline_CoordBox->add_cubic_curve();

    // Add buttons (from left to right)
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreateCurveDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}


void CreateCurveDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            this->create_shape();
            break;
        }
        case Gtk::RESPONSE_CANCEL:
        {
            std::cout << "User cancelled the operation." << std::endl;
            break;
        }
        case Gtk::RESPONSE_DELETE_EVENT:
        {
            std::cout << "User shut the window." << std::endl;
            break;
        }
    }
}


void CreateCurveDialog::create_shape() {

    ShapeBuilder *builder = ShapeBuilder::instance();
    const std::string name = m_nameEntry->get_text().raw();

    if (!name.empty()) {
        std::vector<Coord<double>*> coords;
        bool coords_filled;
        switch (m_notebook->get_current_page())
        {
            case CURVE_BEZIER_CUBIC: coords_filled = m_bezier_CoordBox->fill_coords(coords); break;
            case CURVE_BSPLINE: coords_filled = m_bspline_CoordBox->fill_coords(coords); break;
        }
        if (coords_filled) {

            // Check for minimum number of points.
            if (coords.size() >= 4) {
                m_minVertices = true;
                builder->add_name(name);
                for (unsigned i = 0; i < coords.size(); i++) {
                    builder->add_point(coords[i]->x(), coords[i]->y(), coords[i]->z());
                }
                std::cout << "Added curve to ShapeBuilder." << std::endl;
            } else {
                std::cout << "Rolling back." << std::endl;
                builder->rollback();
            }
        }
        // Clean coords
        for_each (coords.begin(),
                  coords.end(),
                  DeleteList<Coord<double>*>());
    }
}


void CreateCurveDialog::on_page_switch(Widget* page, guint page_number)
{
    DEBUG_MSG("Page switched to " << page_number);
    switch (page_number)
    {
        case CURVE_BEZIER_CUBIC:
        {
            DEBUG_MSG("- Cubic Bézier curve selected");
            m_bspline_CoordBox->clear();
            m_bspline_CoordBox->add_cubic_curve();
            break;
        }
        case CURVE_BSPLINE:
        {
            DEBUG_MSG("- B-Spline curve selected");
            m_bezier_CoordBox->clear();
            m_bezier_CoordBox->add_cubic_curve();
            break;
        }
    }
    show_all_children();
}

void CreateCurveDialog::on_add_bezier_curve_button_clicked()
{
    if (m_bezier_CoordBox->entries_filled()) {
        m_bezier_CoordBox->add_bezier_curve();
    } else {
        this->show_unfilled_entries_dialog("Fill all the other entries before adding a new curve.");
    }
    show_all_children();
}


void CreateCurveDialog::on_add_bspline_point_button_clicked()
{
    if (m_bspline_CoordBox->entries_filled()) {
        m_bspline_CoordBox->add_coord();
    } else {
        this->show_unfilled_entries_dialog("Fill all the other entries before adding a new point.");
    }
    show_all_children();
}


void CreateCurveDialog::show_unfilled_entries_dialog(const std::string &secondary_message)
{
    Gtk::MessageDialog dialog(*this,
            "There are unfilled entries.",
            false,  // Markup
            Gtk::MessageType::MESSAGE_WARNING,
            Gtk::ButtonsType::BUTTONS_OK,
            true);  // Modal
    dialog.set_secondary_text(secondary_message);
    dialog.run();
}


ShapeType CreateCurveDialog::selected_curve_type() const
{
    ShapeType type;
    switch (m_notebook->get_current_page())
    {
        case CURVE_BEZIER_CUBIC:
        {
            type = ShapeType::BEZIER_CUBIC;
            break;
        }
        case CURVE_BSPLINE:
        {
            type = ShapeType::BSPLINE;
            break;
        }
    }
    return type;
}