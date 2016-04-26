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

CreateCurveDialog::CreateCurveDialog(const Glib::ustring & title) :
    Dialog(title, true),
    m_minVertices(false),
    m_coordBox(Gtk::manage(new CoordBox())),
    m_nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    m_nameEntry(Gtk::manage(new Gtk::Entry()))
{
    set_size_request(-1, 200);
    set_resizable(false);
    set_border_width(10);

    // Entry for the name
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*m_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*m_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_spacing(0);
    name_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox, Gtk::PACK_SHRINK, 5);

    Gtk::Frame * const coord_frame = Gtk::manage(new Gtk::Frame("Points"));
    Gtk::ScrolledWindow * const scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());

    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window->set_size_request(-1, 150);
    scrolled_window->set_border_width(5);
    scrolled_window->add(*m_coordBox);
    m_coordBox->set_spacing(0);
    coord_frame->add(*scrolled_window);
    get_content_area()->pack_start(*coord_frame, Gtk::PACK_SHRINK, 0);

    // Entries for the coordinates
    CreateCurveDialog::add_curve();

    // Add buttons (from left to right)
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("Add curve", Gtk::RESPONSE_APPLY);
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
        case Gtk::RESPONSE_APPLY:
        {
            std::cout << "User required to add another curve." << std::endl;
            this->add_curve();
            signal_response().emission_stop();
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
        m_coordBox->fill_coords(coords);

        // Check for minimum number of points.
        if (coords.size() >= 4) {
            m_minVertices = true;
            builder->add_name(name);
            for (unsigned i = 0; i < coords.size(); i++) {
                builder->add_point(coords[i]->x(), coords[i]->y());
            }
            std::cout << "Added curve to ShapeBuilder." << std::endl;
        } else {
            std::cout << "Rolling back." << std::endl;
            builder->rollback();
        }

        // Clean coords
        for_each (coords.begin(),
                  coords.end(),
                  DeleteList<Coord<double>*>());
    }
}

// Called every time the user clicks the "Add point" button.
void CreateCurveDialog::add_curve() {
    // Add another curve to be concatenated (4 points only)
    for (unsigned i = 0; i < 4; i++) {
        m_coordBox->add_coord();
    }
    show_all_children();
}