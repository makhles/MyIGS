// TransformationDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <gtkmm/radiobutton.h>
#include "TransformationDialog.hpp"
#include "TMatrixBuilder.hpp"
#include "TransformationType.hpp"

TransformationDialog::TransformationDialog(const Glib::ustring &title) :
    Dialog(title, true),
    m_notebook(Gtk::manage(new Gtk::Notebook())),
    m_dxEntry(Gtk::manage(new Gtk::Entry())),
    m_dyEntry(Gtk::manage(new Gtk::Entry())),
    m_sxEntry(Gtk::manage(new Gtk::Entry())),
    m_syEntry(Gtk::manage(new Gtk::Entry())),
    m_xEntry(Gtk::manage(new Gtk::Entry())),
    m_yEntry(Gtk::manage(new Gtk::Entry())),
    m_angleEntry(Gtk::manage(new Gtk::Entry())),
    m_xLabel(Gtk::manage(new Gtk::Label("x:"))),
    m_yLabel(Gtk::manage(new Gtk::Label("y:"))),
    m_origin_rbutton(true),
    m_point_rbutton(false),
    m_centroid_rbutton(false)
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

    Gtk::VBox * const radio_box = Gtk::manage(new Gtk::VBox());
    Gtk::HBox * const rotEntry_box = Gtk::manage(new Gtk::HBox());
    Gtk::RadioButton * const origin_rbutton = Gtk::manage(new Gtk::RadioButton("Rotate about origin"));
    Gtk::RadioButton * const centroid_rbutton = Gtk::manage(new Gtk::RadioButton("Rotate about centroid"));
    Gtk::RadioButton * const point_rbutton = Gtk::manage(new Gtk::RadioButton("Rotate about an arbitrary point"));
    Gtk::Label * const angleLabel = Gtk::manage(new Gtk::Label("Angle:"));

    m_xEntry->set_width_chars(6);
    m_yEntry->set_width_chars(6);
    m_angleEntry->set_width_chars(6);

    radio_box->pack_start(*origin_rbutton, Gtk::PACK_SHRINK, 5);
    radio_box->pack_start(*centroid_rbutton, Gtk::PACK_SHRINK, 5);
    radio_box->pack_start(*point_rbutton, Gtk::PACK_SHRINK, 5);

    Gtk::RadioButton::Group group = origin_rbutton->get_group();
    centroid_rbutton->set_group(group);
    point_rbutton->set_group(group);
    origin_rbutton->set_active();

    centroid_rbutton->signal_clicked().connect((sigc::mem_fun(*this,
            &TransformationDialog::handle_centroid_rbutton_toggled)));
    point_rbutton->signal_clicked().connect((sigc::mem_fun(*this,
            &TransformationDialog::handle_point_rbutton_toggled)));
    origin_rbutton->signal_clicked().connect((sigc::mem_fun(*this,
            &TransformationDialog::handle_origin_rbutton_toggled)));

    rotEntry_box->pack_start(*angleLabel, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_angleEntry, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_xLabel, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_xEntry, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_yLabel, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_yEntry, Gtk::PACK_SHRINK, 5);

    rotation_box->pack_start(*radio_box, Gtk::PACK_SHRINK, 10);
    rotation_box->pack_start(*rotEntry_box, Gtk::PACK_SHRINK, 10);

// --------------------------------------------------------------------------------------------- //

    // Pack the main containers into the main box
    get_content_area()->pack_start(*m_notebook, Gtk::PACK_SHRINK, 0);

    // Action buttons (from left to right)
    this->add_button("Cancel", Gtk::RESPONSE_CANCEL);
    this->add_button("OK", Gtk::RESPONSE_OK);

    signal_response().connect_notify(sigc::mem_fun(*this, &TransformationDialog::on_my_response));
    set_default_response(Gtk::RESPONSE_OK);
    show_all_children();

    // Rotation about an arbitrary point is not enabled by default
    this->hide_reference_point();
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
    double angle, x, y;
    std::stringstream str_angle, str_x, str_y;

    str_angle << m_angleEntry->get_text().raw();

    if (str_angle.str().size() != 0) {
        str_angle >> angle;

        if (m_point_rbutton) {

            str_x << m_xEntry->get_text().raw();
            str_y << m_yEntry->get_text().raw();

            // Check for empty entries
            if (str_x.str().size() != 0 && str_y.str().size() != 0) {
                str_x >> x;
                str_y >> y;

                TMatrixBuilder::instance()->createRotationMatrix(angle, x, y);
                success = true;
            }
        } else {
            x = y = 0;
            if (m_centroid_rbutton) {
                TMatrixBuilder::instance()->createRotationMatrix(angle);
            } else {
                TMatrixBuilder::instance()->createRotationMatrix(angle, x, y);
            }
            success = true;
        }
    }
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


void TransformationDialog::handle_origin_rbutton_toggled() {
    m_origin_rbutton = true;
    m_point_rbutton = false;
    m_centroid_rbutton = false;
    this->hide_reference_point();
}


void TransformationDialog::handle_point_rbutton_toggled() {
    m_point_rbutton = true;
    m_origin_rbutton = false;
    m_centroid_rbutton = false;
    this->show_reference_point();
}


void TransformationDialog::handle_centroid_rbutton_toggled() {
    m_centroid_rbutton = true;
    m_point_rbutton = false;
    m_origin_rbutton = false;
    this->hide_reference_point();
}


void TransformationDialog::show_reference_point() {
    m_angleEntry->set_text("");
    m_xEntry->show();
    m_yEntry->show();
    m_xLabel->show();
    m_yLabel->show();
    
}


void TransformationDialog::hide_reference_point() {
    m_angleEntry->set_text("");
    m_xEntry->set_text("");
    m_yEntry->set_text("");
    m_xEntry->hide();
    m_yEntry->hide();
    m_xLabel->hide();
    m_yLabel->hide();
}