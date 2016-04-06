// TransformationDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TransformationDialog.hpp"

TransformationDialog::TransformationDialog(const Glib::ustring &title) :
    Dialog(title, true),
    m_transformations(Gtk::manage(new Gtk::ListViewText(0))),  // 0 columns
    m_dxEntry(Gtk::manage(new Gtk::Entry())),
    m_dyEntry(Gtk::manage(new Gtk::Entry()))
{
    set_resizable(false);
    set_border_width(10);

    Gtk::HBox * const main_box = Gtk::manage(new Gtk::HBox());

    // The tabbed pane
    Gtk::Notebook * const notebook = Gtk::manage(new Gtk::Notebook());

    // Transformation main boxes
    Gtk::VBox * const translation_box = Gtk::manage(new Gtk::VBox());
    Gtk::VBox * const scaling_box = Gtk::manage(new Gtk::VBox());
    Gtk::VBox * const rotation_box = Gtk::manage(new Gtk::VBox());

    // Transformation labels
     Gtk::Label * const translation_label = Gtk::manage(new Gtk::Label("Translation"));
    Gtk::Label * const scaling_label = Gtk::manage(new Gtk::Label("Scaling"));
    Gtk::Label * const rotation_label = Gtk::manage(new Gtk::Label("Rotation"));

    // Transformation content
    Gtk::Label * const label2 = Gtk::manage(new Gtk::Label("Scaling"));
    Gtk::Label * const label3 = Gtk::manage(new Gtk::Label("Rotation"));

    scaling_box->pack_start(*label2, Gtk::PACK_SHRINK, 0);
    rotation_box->pack_start(*label3, Gtk::PACK_SHRINK, 0);

    // Add the pages to the tab pane
    notebook->append_page(*translation_box, *translation_label);
    notebook->append_page(*scaling_box, *scaling_label);
    notebook->append_page(*rotation_box, *rotation_label);

    // Add signal handler to tab switching
    notebook->signal_switch_page().connect(sigc::mem_fun(*this, &TransformationDialog::on_notebook_switch_page));


// --------------------------------------------------------------------------------------------- //
// --------------------------------------- Translation ----------------------------------------- //

    Gtk::HBox * const delta_box = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const dxLabel = Gtk::manage(new Gtk::Label("dx:"));
    Gtk::Label * const dyLabel = Gtk::manage(new Gtk::Label("dy:"));

    m_dxEntry->set_width_chars(6);
    m_dyEntry->set_width_chars(6);

    delta_box->pack_start(*dxLabel, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*m_dxEntry, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*dyLabel, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*m_dyEntry, Gtk::PACK_SHRINK, 5);

    translation_box->pack_start(*delta_box, Gtk::PACK_SHRINK, 10);

// --------------------------------------------------------------------------------------------- //
// ----------------------------------------- Scaling ------------------------------------------- //


// --------------------------------------------------------------------------------------------- //
// ----------------------------------------- Rotation ------------------------------------------ //

    // The left box widgets
    Gtk::VBox * const list_box = Gtk::manage(new Gtk::VBox());
    Gtk::ScrolledWindow * const scroll_window = Gtk::manage(new Gtk::ScrolledWindow());
    Gtk::Button * const add_button = Gtk::manage(new Gtk::Button("Add"));
    Gtk::Button * const rem_button = Gtk::manage(new Gtk::Button("Remove"));

    // Pack the left box widgets
    scroll_window->add(*m_transformations);
    scroll_window->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    list_box->pack_start(*scroll_window, Gtk::PACK_EXPAND_WIDGET, 0);
    list_box->pack_start(*add_button, Gtk::PACK_SHRINK, 0);
    list_box->pack_start(*rem_button, Gtk::PACK_SHRINK, 0);

    // Add signal handlers to the list box buttons
    add_button->signal_clicked().connect(sigc::mem_fun(*this, &TransformationDialog::on_add_button_clicked));
    rem_button->signal_clicked().connect(sigc::mem_fun(*this, &TransformationDialog::on_rem_button_clicked));

    // Pack the main containers into the main box
    get_content_area()->pack_start(*main_box);
    main_box->pack_start(*notebook, Gtk::PACK_SHRINK, 0);
    main_box->pack_start(*list_box, Gtk::PACK_SHRINK, 0);

    // Action buttons (from left to right)
    this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    this->add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &TransformationDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}


void TransformationDialog::on_add_button_clicked() {
    std::cout << "Adding transformation..." << std::endl;
}


void TransformationDialog::on_rem_button_clicked() {
    std::cout << "Removing transformation..." << std::endl;
}


void TransformationDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            std::cout << "User pressed OK." << std::endl;
            this->applyTransformations();
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


void TransformationDialog::on_notebook_switch_page(Gtk::Widget* page, guint page_number) {
    std::cout << "Switched to tab with index " << page_number << std::endl;
}


void TransformationDialog::applyTransformations() {
    std::cout << "Applying all transformations." << std::endl;
}

