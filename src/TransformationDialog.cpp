// TransformationDialog.cpp
// Authors: Leonardo Vailatti Eichstaedt
//          Makhles Reuter Lange

#include <iostream>
#include <gtkmm/radiobutton.h>
#include "InterfaceController.hpp"
#include "TransformationDialog.hpp"
#include "TransformationType.hpp"
#include "ObjectsTreeView.hpp"
#include "CoordBox.hpp"
#include "DeleteList.hpp"

/* ============================================================================================= */
TransformationDialog::TransformationDialog(const Glib::ustring &title,
        InterfaceController *controller, ObjectsTreeView *objTreeView) :
/* ============================================================================================= */
    Dialog(title, true),
    m_controller(controller),
    m_objTreeView(objTreeView),
    m_notebook(Gtk::manage(new Gtk::Notebook())),
    m_dxEntry(Gtk::manage(new Gtk::Entry())),
    m_dyEntry(Gtk::manage(new Gtk::Entry())),
    m_dzEntry(Gtk::manage(new Gtk::Entry())),
    m_sxEntry(Gtk::manage(new Gtk::Entry())),
    m_syEntry(Gtk::manage(new Gtk::Entry())),
    m_szEntry(Gtk::manage(new Gtk::Entry())),
    m_axEntry(Gtk::manage(new Gtk::Entry())),
    m_ayEntry(Gtk::manage(new Gtk::Entry())),
    m_azEntry(Gtk::manage(new Gtk::Entry())),
    m_bxEntry(Gtk::manage(new Gtk::Entry())),
    m_byEntry(Gtk::manage(new Gtk::Entry())),
    m_bzEntry(Gtk::manage(new Gtk::Entry())),
    m_angleEntry(Gtk::manage(new Gtk::Entry())),
    m_coordBox(Gtk::manage(new CoordBox())),
    m_own_axis_rb(true),
    m_rnd_axis_rb(false)
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
    Gtk::Label * const dzLabel = Gtk::manage(new Gtk::Label("dz:"));

    m_dxEntry->set_width_chars(6);
    m_dyEntry->set_width_chars(6);
    m_dzEntry->set_width_chars(6);

    delta_box->pack_start(*dxLabel, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*m_dxEntry, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*dyLabel, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*m_dyEntry, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*dzLabel, Gtk::PACK_SHRINK, 5);
    delta_box->pack_start(*m_dzEntry, Gtk::PACK_SHRINK, 5);

    translation_box->pack_start(*delta_box, Gtk::PACK_SHRINK, 10);

// --------------------------------------------------------------------------------------------- //
// ----------------------------------------- Scaling ------------------------------------------- //

    Gtk::HBox * const sfactor_box = Gtk::manage(new Gtk::HBox());  // Scaling factor box
    Gtk::Label * const sxLabel = Gtk::manage(new Gtk::Label("sx:"));
    Gtk::Label * const syLabel = Gtk::manage(new Gtk::Label("sy:"));
    Gtk::Label * const szLabel = Gtk::manage(new Gtk::Label("sz:"));

    m_sxEntry->set_width_chars(6);
    m_syEntry->set_width_chars(6);
    m_szEntry->set_width_chars(6);

    sfactor_box->pack_start(*sxLabel, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*m_sxEntry, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*syLabel, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*m_syEntry, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*szLabel, Gtk::PACK_SHRINK, 5);
    sfactor_box->pack_start(*m_szEntry, Gtk::PACK_SHRINK, 5);

    scaling_box->pack_start(*sfactor_box, Gtk::PACK_SHRINK, 10);

// --------------------------------------------------------------------------------------------- //
// ----------------------------------------- Rotation ------------------------------------------ //

    Gtk::VBox * const radio_box = Gtk::manage(new Gtk::VBox());
    Gtk::HBox * const rotEntry_box = Gtk::manage(new Gtk::HBox());
    Gtk::RadioButton * const own_axis_rb = Gtk::manage(new Gtk::RadioButton("Rotate about own axis"));
    Gtk::RadioButton * const rnd_axis_rb = Gtk::manage(new Gtk::RadioButton("Rotate about given axis"));
    Gtk::Label * const angleLabel = Gtk::manage(new Gtk::Label("Angle:"));

    m_angleEntry->set_width_chars(6);

    radio_box->pack_start(*own_axis_rb, Gtk::PACK_SHRINK, 5);
    radio_box->pack_start(*rnd_axis_rb, Gtk::PACK_SHRINK, 5);

    Gtk::RadioButton::Group group = own_axis_rb->get_group();
    rnd_axis_rb->set_group(group);
    own_axis_rb->set_active();

    rnd_axis_rb->signal_clicked().connect((sigc::mem_fun(*this,
            &TransformationDialog::handle_rnd_axis_rbutton_toggled)));
    own_axis_rb->signal_clicked().connect((sigc::mem_fun(*this,
            &TransformationDialog::handle_own_axis_rbutton_toggled)));

    rotEntry_box->pack_start(*angleLabel, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_angleEntry, Gtk::PACK_SHRINK, 5);
    rotEntry_box->pack_start(*m_coordBox, Gtk::PACK_SHRINK, 5);

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
    this->hide_rnd_axis();
}

/* ============================================================================================= */
void TransformationDialog::on_my_response(int response_id)
/* ============================================================================================= */
{
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

/* ============================================================================================= */
bool TransformationDialog::translate()
/* ============================================================================================= */
{
    bool success = false;
    std::stringstream str_dx, str_dy, str_dz;

    // Get input data from dialog box entries
    str_dx << m_dxEntry->get_text().raw();
    str_dy << m_dyEntry->get_text().raw();
    str_dz << m_dzEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_dx.str().size() != 0 && str_dy.str().size() != 0 && str_dz.str().size() != 0) {
        str_dx >> m_dx;
        str_dy >> m_dy;
        str_dy >> m_dz;
        success = true;
        m_controller->translate(*this);
    }
    return success;
}

/* ============================================================================================= */
bool TransformationDialog::scale()
/* ============================================================================================= */
{
    bool success = false;
    std::stringstream str_sx, str_sy, str_sz;

    // Get input data from dialog box entries
    str_sx << m_sxEntry->get_text().raw();
    str_sy << m_syEntry->get_text().raw();
    str_sz << m_szEntry->get_text().raw();
    
    /* Check for empty entries */
    if (str_sx.str().size() != 0 && str_sy.str().size() != 0 && str_sz.str().size() != 0) {
        str_sx >> m_sx;
        str_sy >> m_sy;
        str_sz >> m_sz;
        success = true;
        m_controller->scale(*this);
    }
    return success;
}

/* ============================================================================================= */
bool TransformationDialog::rotate()
/* ============================================================================================= */
{
    bool success = false;
    std::stringstream str_angle;

    str_angle << m_angleEntry->get_text().raw();

    if (str_angle.str().size() != 0) {
        str_angle >> m_angle;

        if (m_rnd_axis_rb) {

            std::vector<Coord<double>*> coords;
            bool coords_filled = m_coordBox->fill_coords(coords);
            if (coords_filled) {
                m_rax = coords[0]->x();
                m_ray = coords[0]->y();
                m_raz = coords[0]->z();
                m_rbx = coords[1]->x();
                m_rby = coords[1]->y();
                m_rbz = coords[1]->z();
                success = true;
                m_controller->rotate(*this);
            }
            // Clean coords
            for_each (coords.begin(),
                      coords.end(),
                      DeleteList<Coord<double>*>());
        } else {
            // Arbitrary rotation axis (unit vector along the Z axis)
            m_rax = 0.0;
            m_ray = 0.0;
            m_raz = 0.0;
            m_rbx = 0.0;
            m_rby = 0.0;
            m_rbz = 1.0;
            success = true;
            m_controller->rotate(*this);
        }
    }
    return success;
}

/* ============================================================================================= */
bool TransformationDialog::transform()
/* ============================================================================================= */
{
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

/* ============================================================================================= */
void TransformationDialog::handle_own_axis_rbutton_toggled()
/* ============================================================================================= */
{
    m_own_axis_rb = true;
    m_rnd_axis_rb = false;
    this->hide_rnd_axis();
}

/* ============================================================================================= */
void TransformationDialog::handle_rnd_axis_rbutton_toggled()
/* ============================================================================================= */
{
    m_rnd_axis_rb = true;
    m_own_axis_rb = false;
    this->show_rnd_axis();
}

/* ============================================================================================= */
void TransformationDialog::show_rnd_axis()
/* ============================================================================================= */
{
    m_angleEntry->set_text("");
    m_coordBox->show_coords();
}

/* ============================================================================================= */
void TransformationDialog::hide_rnd_axis()
/* ============================================================================================= */
{
    m_angleEntry->set_text("");
    m_coordBox->hide_coords();
}

/* ============================================================================================= */
std::string TransformationDialog::get_selected_object() const
/* ============================================================================================= */
{
    return m_objTreeView->get_selected_object();
}