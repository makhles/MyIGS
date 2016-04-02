// CreateWireframeDialog.hpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <gtkmm/entry.h>
#include <gtkmm/label.h>
#include <gtkmm/button.h>
#include <iostream>
#include "CreateWireframeDialog.hpp"
#include "ShapeBuilder.hpp"

#define GTK_RESPONSE_ADD 999

CreateWireframeDialog::CreateWireframeDialog(const Glib::ustring & title) :
    Dialog(title, true),
    _nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    _nameEntry(Gtk::manage(new Gtk::Entry()))

{
    set_resizable(false);
    set_border_width(10);

    // Entry for the name
    Gtk::HBox * const name_hbox = Gtk::manage(new Gtk::HBox());
    name_hbox->pack_start(*_nameLabel, Gtk::PACK_SHRINK, 0);
    name_hbox->pack_start(*_nameEntry, Gtk::PACK_EXPAND_WIDGET, 0);
    name_hbox->set_homogeneous(false);

    get_content_area()->pack_start(*name_hbox);

    // Entries for the coordinates
    this->addCoord();
    this->addCoord();
    this->addCoord();

    // Add buttons (from left to right)
    add_button("Cancel", Gtk::RESPONSE_CANCEL);
    add_button("Add point", Gtk::RESPONSE_APPLY);
    add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &CreateWireframeDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}

void CreateWireframeDialog::on_button_add_clicked() {
    this->addCoord();
}


void CreateWireframeDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            // double x1, x2, y1, y2;
            // std::stringstream sX1, sY1, sX2, sY2;

            // /* Get input data from dialog box entries */
            // const std::string name = _nameEntry->get_text().raw();
            // sX1 << _x1Entry->get_text().raw();
            // sY1 << _y1Entry->get_text().raw();
            // sX2 << _x2Entry->get_text().raw();
            // sY2 << _y2Entry->get_text().raw();

            // if (!name.empty() && sX1.str().size() != 0 && sY1.str().size() != 0
            //         && sX2.str().size() != 0 && sY2.str().size() != 0) {

            //     sX1 >> x1;
            //     sY1 >> y1;
            //     sX2 >> x2;
            //     sY2 >> y2;

            //     /* Create the new point */
            //     ShapeBuilder *builder = ShapeBuilder::instance();
            //     builder->addName(name);
            //     builder->addPoint(x1, y1);
            //     builder->addPoint(x2, y2);
                std::cout << "Added wireframe to ShapeBuilder." << std::endl;
            // }
            break;
        }
        case Gtk::RESPONSE_APPLY:
        {
            std::cout << "User required to add another point." << std::endl;
            this->addCoord();
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

// Called every time the user clicks the "Add point" button.
void CreateWireframeDialog::addCoord() {

    // Used for naming each coordinate, like x0, x1, y0, y1, etc.
    // Every time a new point is added, m_coordEntries increases by 2.
    int pNumber = m_coordEntries.size() / 2;
    const std::string str_xCoord = "x" + std::to_string(pNumber) + ": ";
    const std::string str_yCoord = "y" + std::to_string(pNumber) + ": ";

    Gtk::HBox * const hbox = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const xLabel = Gtk::manage(new Gtk::Label(str_xCoord));
    Gtk::Label * const yLabel = Gtk::manage(new Gtk::Label(str_yCoord));
    Gtk::Entry * const xEntry = Gtk::manage(new Gtk::Entry());
    Gtk::Entry * const yEntry = Gtk::manage(new Gtk::Entry());

    xEntry->set_width_chars(10);
    yEntry->set_width_chars(10);

    hbox->pack_start(*xLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*xEntry, Gtk::PACK_SHRINK, 0);
    hbox->pack_start(*yLabel, Gtk::PACK_EXPAND_WIDGET, 0);
    hbox->pack_start(*yEntry, Gtk::PACK_SHRINK, 0);
    hbox->set_homogeneous(false);

    get_content_area()->pack_start(*hbox);
    show_all_children();

    // Keep track of entries to get their values
    m_coordEntries.push_back(xEntry);
    m_coordEntries.push_back(yEntry);
}