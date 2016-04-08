// TransformationDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include "TransformationDialog.hpp"
#include "TMatrixBuilder.hpp"
#include "TransformationType.hpp"

TransformationDialog::TransformationDialog(const Glib::ustring &title) :
    Dialog(title, true),
    m_notebook(Gtk::manage(new Gtk::Notebook())),
    m_dxEntry(Gtk::manage(new Gtk::Entry())),
    m_dyEntry(Gtk::manage(new Gtk::Entry())),
    m_sxEntry(Gtk::manage(new Gtk::Entry())),
    m_syEntry(Gtk::manage(new Gtk::Entry()))
{
    set_resizable(false);
    set_border_width(10);

    // Transformation main boxes
    Gtk::VBox * const translation_box = Gtk::manage(new Gtk::VBox());
    Gtk::VBox * const scaling_box = Gtk::manage(new Gtk::VBox());
    Gtk::VBox * const rotation_box = Gtk::manage(new Gtk::VBox());

    // Transformation labels
    Gtk::Label * const translation_label = Gtk::manage(new Gtk::Label("Translation"));
    Gtk::Label * const scaling_label = Gtk::manage(new Gtk::Label("Scaling"));
    Gtk::Label * const rotation_label = Gtk::manage(new Gtk::Label("Rotation"));

    // Add the pages to the tab pane
    // Pages added in the order specified in the file TransformationType.hpp
    m_notebook->append_page(*translation_box, *translation_label);
    m_notebook->append_page(*scaling_box, *scaling_label);
    m_notebook->append_page(*rotation_box, *rotation_label);

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



// --------------------------------------------------------------------------------------------- //

    // Pack the main containers into the main box
    get_content_area()->pack_start(*m_notebook, Gtk::PACK_SHRINK, 0);

    // Action buttons (from left to right)
    this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    this->add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &TransformationDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();
}


void TransformationDialog::on_my_response(int response_id) {
    switch (response_id) {
        case Gtk::RESPONSE_OK:
        {
            std::cout << "User pressed OK." << std::endl;
            if (!this->transform()) {
                std::cout << "There's at least one empty Entry. Nothing to do." << std::endl;
                signal_response().emission_stop();
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


bool TransformationDialog::translate() {
    bool success = false;
    double dx, dy;
    std::stringstream str_dx, str_dy;

    /* Get input data from dialog box entries */
    str_dx << m_dxEntry->get_text().raw();
    str_dy << m_dyEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_dx.str().size() != 0 && str_dy.str().size() != 0) {
        str_dx >> dx;
        str_dy >> dy;

        TMatrixBuilder::instance()->createTranslationMatrix(dx, dy);
        success = true;
    }
    return success;
}


bool TransformationDialog::scale() {
    bool success = false;
    double sx, sy;
    std::stringstream str_sx, str_sy;

    /* Get input data from dialog box entries */
    str_sx << m_sxEntry->get_text().raw();
    str_sy << m_syEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_sx.str().size() != 0 && str_sy.str().size() != 0) {
        str_sx >> sx;
        str_sy >> sy;

        TMatrixBuilder::instance()->createScalingMatrix(sx, sy);
        success = true;
    }
    return success;
}


bool TransformationDialog::rotate() {
    bool success = false;
    return success;
}


bool TransformationDialog::transform() {
    bool success = false;
    switch (m_notebook->get_current_page())
    {
        case static_cast<int>(TransformationType::TRANSLATION) :
        {
            success = this->translate();
            break;
        }
        case static_cast<int>(TransformationType::SCALING) :
        {
            success = this->scale();
            break;
        }
        case static_cast<int>(TransformationType::ROTATION) :
        {
            success = this->rotate();
            break;
        }
    }
    return success;
}