// TransformationDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TransformationDialog.hpp"
#include "TMatrixBuilder.hpp"

TransformationDialog::TransformationDialog(const Glib::ustring &title) :
    Dialog(title, true),
    m_transformations(Gtk::manage(new Gtk::ListViewText(1))),  // 1 column
    m_dxEntry(Gtk::manage(new Gtk::Entry())),
    m_dyEntry(Gtk::manage(new Gtk::Entry())),
    m_sxEntry(Gtk::manage(new Gtk::Entry())),
    m_syEntry(Gtk::manage(new Gtk::Entry())),
    m_translationsCount(0),
    m_scalingCount(0)
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

    Gtk::HBox * const sfactor_box = Gtk::manage(new Gtk::HBox());  // Scaling factor box
    Gtk::Label * const sxLabel = Gtk::manage(new Gtk::Label("sx:"));
    Gtk::Label * const syLabel = Gtk::manage(new Gtk::Label("sy:"));

    m_sxEntry->set_width_chars(6);
    m_syEntry->set_width_chars(6);

    sfactor_box->pack_start(*sxLabel, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*m_sxEntry, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*syLabel, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*m_syEntry, Gtk::PACK_SHRINK, 5);

    scaling_box->pack_start(*sfactor_box, Gtk::PACK_SHRINK, 10);

// --------------------------------------------------------------------------------------------- //
// ----------------------------------------- Rotation ------------------------------------------ //



    // The left box widgets
    m_transformations->set_column_title(0, "Transformations:");
    Gtk::VBox * const list_box = Gtk::manage(new Gtk::VBox());
    Gtk::ScrolledWindow * const scroll_window = Gtk::manage(new Gtk::ScrolledWindow());
    Gtk::Button * const add_button = Gtk::manage(new Gtk::Button("Add"));
    Gtk::Button * const rem_button = Gtk::manage(new Gtk::Button("Remove"));

    // Pack the left box widgets
    scroll_window->set_size_request(150,100);
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
    switch (m_transformType) {
        case TransformationType::TRANSLATION:
        {
            this->addTranslation();
            break;
        }
        case TransformationType::SCALING:
        {
            this->addScaling();
            break;
        }
        case TransformationType::ROTATION:
        {
            break;
        }
    }
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
    switch (page_number) {
        case 0:
        {
            m_transformType = TransformationType::TRANSLATION;
            break;
        }
        case 1:
        {
            m_transformType = TransformationType::SCALING;
            break;
        }
        case 2:
        {
            m_transformType = TransformationType::ROTATION;
            break;
        }
    }
}


void TransformationDialog::addTranslation() {
    double dx, dy;
    std::stringstream str_dx, str_dy;

    /* Get input data from dialog box entries */
    str_dx << m_dxEntry->get_text().raw();
    str_dy << m_dyEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_dx.str().size() != 0 && str_dy.str().size() != 0) {
        str_dx >> dx;
        str_dy >> dy;

        TMatrixBuilder::instance()->addTranslation(dx, dy);
        m_transformations->append("Translation " + std::to_string(m_translationsCount));
        m_translationsCount++;
        std::cout << "Added new translation." << std::endl;
    }
}


void TransformationDialog::addScaling() {
    double sx, sy;
    std::stringstream str_sx, str_sy;

    /* Get input data from dialog box entries */
    str_sx << m_sxEntry->get_text().raw();
    str_sy << m_syEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_sx.str().size() != 0 && str_sy.str().size() != 0) {
        str_sx >> sx;
        str_sy >> sy;

        TMatrixBuilder::instance()->addScaling(sx, sy);
        m_transformations->append("Scaling " + std::to_string(m_scalingCount));
        m_scalingCount++;
        std::cout << "Added new scaling." << std::endl;
    }
}


void TransformationDialog::applyTransformations() {
    std::cout << "Applying all transformations." << std::endl;
    
}

