// CreatePointDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <iostream>
#include "CreatePointDialog.hpp"
#include "ShapeBuilder.hpp"

CreatePointDialog::CreatePointDialog(const Glib::ustring & title) :
    Dialog(title, true),
    m_nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    m_xLabel(Gtk::manage(new Gtk::Label("x: "))),
    m_yLabel(Gtk::manage(new Gtk::Label("y: "))),
    m_zLabel(Gtk::manage(new Gtk::Label("z: "))),
    m_nameEntry(Gtk::manage(new Gtk::Entry())),
    m_xEntry(Gtk::manage(new Gtk::Entry())),
    m_yEntry(Gtk::manage(new Gtk::Entry())),
    m_zEntry(Gtk::manage(new Gtk::Entry()))
{
    set_resizable(false);
    set_border_width(10);

    /* Entries size */
    m_xEntry->set_width_chars(6);
    m_yEntry->set_width_chars(6);
    m_zEntry->set_width_chars(6);
    
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*m_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*m_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_homogeneous(false);

    Gtk::HBox * const coord_hbox = Gtk::manage(new Gtk::HBox());
    coord_hbox->pack_start(*m_xLabel, Gtk::PACK_EXPAND_PADDING, 0);
    coord_hbox->pack_start(*m_xEntry, Gtk::PACK_SHRINK, 0);
    coord_hbox->pack_start(*m_yLabel, Gtk::PACK_EXPAND_PADDING, 0);
    coord_hbox->pack_start(*m_yEntry, Gtk::PACK_SHRINK, 0);
    coord_hbox->pack_start(*m_zLabel, Gtk::PACK_EXPAND_PADDING, 0);
    coord_hbox->pack_start(*m_zEntry, Gtk::PACK_SHRINK, 0);
    coord_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox);
    get_content_area()->pack_start(*coord_hbox);
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreatePointDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}

CreatePointDialog::~CreatePointDialog() {
}

void CreatePointDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            double x, y, z;
            std::string name;
            std::stringstream stringX, stringY, stringZ;

            /* Get input data from dialog box entries */
            name = m_nameEntry->get_text().raw();
            stringX << m_xEntry->get_text().raw();
            stringY << m_yEntry->get_text().raw();
            stringZ << m_zEntry->get_text().raw();
            
            /* Check for empty entries */
            if (!name.empty() &&
                    stringX.str().size() != 0 &&
                    stringY.str().size() != 0 &&
                    stringZ.str().size() != 0) {
                stringX >> x;
                stringY >> y;
                stringZ >> z;

                /* Create the new point */
                ShapeBuilder::instance()->add_point(name, x, y, z);
                std::cout << "Added point to ShapeBuilder." << std::endl;
            }
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