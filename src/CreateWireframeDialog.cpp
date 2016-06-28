// CreateWireframeDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <vector>
#include "CreateWireframeDialog.hpp"
#include "ShapeBuilder.hpp"
#include "CoordBox.hpp"
#include "Coord.hpp"
#include "DeleteList.hpp"

CreateWireframeDialog::CreateWireframeDialog(const Glib::ustring & title) :
    Dialog(title, true),
    m_filled(false),
    m_minVertices(false),
    m_coordBox(Gtk::manage(new CoordBox())),
    m_nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    m_nameEntry(Gtk::manage(new Gtk::Entry()))
{
    set_size_request(-1, 300);
    set_resizable(false);
    set_border_width(10);

    // Entry for the name
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*m_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*m_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_spacing(0);
    name_hbox->set_homogeneous(false);

    // Check box for filling
    Gtk::CheckButton * const filled_button = Gtk::manage(new Gtk::CheckButton("Filled shape"));
    filled_button->signal_toggled().connect(sigc::mem_fun(*this, &CreateWireframeDialog::on_filled_button_toggled));
    filled_button->set_active(false);

    get_content_area()->pack_start(*name_hbox, Gtk::PACK_SHRINK, 5);
    get_content_area()->pack_start(*filled_button, Gtk::PACK_SHRINK, 5);

    Gtk::Frame * const coord_frame = Gtk::manage(new Gtk::Frame("Points"));
    Gtk::ScrolledWindow * const scrolled_window = Gtk::manage(new Gtk::ScrolledWindow());

    scrolled_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    scrolled_window->set_size_request(400, 150);
    scrolled_window->set_border_width(5);
    scrolled_window->add(*m_coordBox);
    m_coordBox->set_spacing(0);
    coord_frame->add(*scrolled_window);
    get_content_area()->pack_start(*coord_frame, Gtk::PACK_SHRINK, 0);

    // Entries for the coordinates
    m_coordBox->add_coord();
    m_coordBox->add_coord();
    m_coordBox->add_coord();

    // Add buttons (from left to right)
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("Add point", Gtk::RESPONSE_APPLY);
    add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreateWireframeDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}


void CreateWireframeDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            this->create_shape();
            break;
        }
        case Gtk::RESPONSE_APPLY:
        {
            std::cout << "User required to add another point." << std::endl;
            this->add_point();
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


void CreateWireframeDialog::create_shape() {

    ShapeBuilder *builder = ShapeBuilder::instance();
    const std::string name = m_nameEntry->get_text().raw();

    if (!name.empty()) {
        std::vector<Coord<double>*> coords;
        if (m_coordBox->fill_coords(coords)) {

            // Check for minimum number of points.
            if (coords.size() >= 3) {
                m_minVertices = true;
                builder->add_name(name);
                builder->set_filled(m_filled);
                for (unsigned i = 0; i < coords.size(); i++) {
                    builder->add_point(coords[i]->x(), coords[i]->y(), coords[i]->z());
                }
                std::cout << "Added wireframe to ShapeBuilder." << std::endl;
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

// Called every time the user clicks the "Add point" button.
void CreateWireframeDialog::add_point() {
    if (m_coordBox->entries_filled()) {
        m_coordBox->add_coord();
    } else {
        Gtk::MessageDialog dialog(*this,
                "There are unfilled entries.",
                false,  // Markup
                Gtk::MessageType::MESSAGE_WARNING,
                Gtk::ButtonsType::BUTTONS_OK,
                true);  // Modal
        dialog.set_secondary_text("Fill all the other entries before adding a new point.");
        dialog.run();
    }
    show_all_children();
}


void CreateWireframeDialog::on_filled_button_toggled() {
    m_filled ^= true;
}