// CreateLineDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <iostream>
#include "CreateLineDialog.hpp"
#include "ShapeBuilder.hpp"

CreateLineDialog::CreateLineDialog(const Glib::ustring & title) :
    Dialog(title, true),
    _nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    _x1Label(Gtk::manage(new Gtk::Label("x1: "))),
    _x2Label(Gtk::manage(new Gtk::Label("x2: "))),
    _y1Label(Gtk::manage(new Gtk::Label("y1: "))),
    _y2Label(Gtk::manage(new Gtk::Label("y2: "))),
    _nameEntry(Gtk::manage(new Gtk::Entry())),
    _x1Entry(Gtk::manage(new Gtk::Entry())),
    _x2Entry(Gtk::manage(new Gtk::Entry())),
    _y1Entry(Gtk::manage(new Gtk::Entry())),
    _y2Entry(Gtk::manage(new Gtk::Entry()))
{
    set_resizable(false);
    set_border_width(10);

    /* Entries size */
    _x1Entry->set_width_chars(6);
    _x2Entry->set_width_chars(6);
    _y1Entry->set_width_chars(6);
    _y2Entry->set_width_chars(6);

    // Entry for the name
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_homogeneous(false);

    // Entries for the first Point
    Gtk::HBox * const coord1_hbox = Gtk::manage(new Gtk::HBox());
    coord1_hbox->pack_start(*_x1Label, Gtk::PACK_EXPAND_PADDING, 0);
    coord1_hbox->pack_start(*_x1Entry, Gtk::PACK_SHRINK, 0);
    coord1_hbox->pack_start(*_y1Label, Gtk::PACK_EXPAND_PADDING, 0);
    coord1_hbox->pack_start(*_y1Entry, Gtk::PACK_SHRINK, 0);
    coord1_hbox->set_homogeneous(false);

    // Entries for the second Point
    Gtk::HBox * const coord2_hbox = Gtk::manage(new Gtk::HBox());
    coord2_hbox->pack_start(*_x2Label, Gtk::PACK_EXPAND_PADDING, 0);
    coord2_hbox->pack_start(*_x2Entry, Gtk::PACK_SHRINK, 0);
    coord2_hbox->pack_start(*_y2Label, Gtk::PACK_EXPAND_PADDING, 0);
    coord2_hbox->pack_start(*_y2Entry, Gtk::PACK_SHRINK, 0);
    coord2_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox);
    get_content_area()->pack_start(*coord1_hbox);
    get_content_area()->pack_start(*coord2_hbox);
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreateLineDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}

void CreateLineDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            double x1, x2, y1, y2;
            std::stringstream sX1, sY1, sX2, sY2;

            /* Get input data from dialog box entries */
            const std::string name = _nameEntry->get_text().raw();
            sX1 << _x1Entry->get_text().raw();
            sY1 << _y1Entry->get_text().raw();
            sX2 << _x2Entry->get_text().raw();
            sY2 << _y2Entry->get_text().raw();

            if (!name.empty() && sX1.str().size() != 0 && sY1.str().size() != 0
                    && sX2.str().size() != 0 && sY2.str().size() != 0) {

                sX1 >> x1;
                sY1 >> y1;
                sX2 >> x2;
                sY2 >> y2;

                /* Create the new point */
                ShapeBuilder *builder = ShapeBuilder::instance();
                builder->addName(name);
                builder->addPoint(x1, y1);
                builder->addPoint(x2, y2);
                std::cout << "Added line to ShapeBuilder." << std::endl;
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