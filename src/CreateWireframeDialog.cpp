// CreateWireframeDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "CreateWireframeDialog.hpp"
#include "ShapeBuilder.hpp"

CreateWireframeDialog::CreateWireframeDialog(const Glib::ustring & title) :
    Dialog(title, true),
    m_totalPoints(0),
    m_filled(false),
    m_coordBox(Gtk::manage(new Gtk::VBox())),
    m_nameLabel(Gtk::manage(new Gtk::Label("Name: "))),
    m_nameEntry(Gtk::manage(new Gtk::Entry()))

{
    set_size_request(-1, 230);
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
    scrolled_window->set_size_request(-1, 150);
    scrolled_window->set_border_width(5);
    scrolled_window->add(*m_coordBox);
    m_coordBox->set_spacing(0);
    coord_frame->add(*scrolled_window);
    get_content_area()->pack_start(*coord_frame, Gtk::PACK_SHRINK, 0);

    // Entries for the coordinates
    this->add_point();
    this->add_point();
    this->add_point();


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

        builder->add_name(name);
        builder->set_filled(m_filled);
        
        double x, y;
        auto coord = m_coordEntries.cbegin();
        
        while (coord != m_coordEntries.cend()) {
            // Create new stringstreams at every loop iteration
            // to make sure it's totally clear.
            std::stringstream sX, sY;
            sX << (*coord)->get_text().raw();
            coord++;
            sY << (*coord)->get_text().raw();
            coord++;
            
            if (sX.str().size() != 0 && sY.str().size() != 0) {
                sX >> x;
                sY >> y;
                m_totalPoints++;
                builder->add_point(x, y);
            }
        }
        // Check for minimum number of points.
        if (!this->build_wireframe()) {
            std::cout << "Rolling back." << std::endl;
            builder->rollback();
        }
        std::cout << "Added wireframe to ShapeBuilder." << std::endl;
    }
}

// Called every time the user clicks the "Add point" button.
void CreateWireframeDialog::add_point() {

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

    m_coordBox->pack_start(*hbox, Gtk::PACK_EXPAND_WIDGET, 5);;
    show_all_children();

    // Keep track of entries to get their values
    m_coordEntries.push_back(xEntry);
    m_coordEntries.push_back(yEntry);
}


void CreateWireframeDialog::on_filled_button_toggled() {
    m_filled ^= true;
}