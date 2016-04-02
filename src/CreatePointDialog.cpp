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
    _nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    _xLabel(Gtk::manage(new Gtk::Label("x: "))),
    _yLabel(Gtk::manage(new Gtk::Label("y: "))),
    _nameEntry(Gtk::manage(new Gtk::Entry())),
    _xEntry(Gtk::manage(new Gtk::Entry())),
    _yEntry(Gtk::manage(new Gtk::Entry()))
{
    set_resizable(false);
    set_border_width(10);

    /* Entries size */
    _xEntry->set_width_chars(6);
    _yEntry->set_width_chars(6);
    
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_homogeneous(false);

    Gtk::HBox * const coord_hbox = Gtk::manage(new Gtk::HBox());
    coord_hbox->pack_start(*_xLabel, Gtk::PACK_EXPAND_PADDING, 0);
    coord_hbox->pack_start(*_xEntry, Gtk::PACK_SHRINK, 0);
    coord_hbox->pack_start(*_yLabel, Gtk::PACK_EXPAND_PADDING, 0);
    coord_hbox->pack_start(*_yEntry, Gtk::PACK_SHRINK, 0);
    coord_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox);
    get_content_area()->pack_start(*coord_hbox);
    add_button("OK", Gtk::RESPONSE_OK);
    add_button("Cancel", Gtk::RESPONSE_CANCEL);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreatePointDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_CANCEL);
    show_all_children();
}

CreatePointDialog::~CreatePointDialog() {
}

void CreatePointDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            double x, y;
            std::string name;
            std::stringstream stringX, stringY;

            /* Get input data from dialog box entries */
            name = _nameEntry->get_text().raw();
            stringX << _xEntry->get_text().raw();
            stringY << _yEntry->get_text().raw();
            
            /* Check for empty entries */
            if (!name.empty() && stringX.str().size() != 0 && stringY.str().size() != 0) {
                stringX >> x;
                stringY >> y;

                /* Create the new point */
                ShapeBuilder::instance()->addPoint(name, x, y);
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