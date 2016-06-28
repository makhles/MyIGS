/* MyIGS.cpp */

#include <iostream>
#include "MyIGS.hpp"
#include "InterfaceController.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "CreatePointDialog.hpp"
#include "CreateLineDialog.hpp"
#include "CreateWireframeDialog.hpp"
#include "CreateCurveDialog.hpp"
#include "ObjectsTreeView.hpp"
#include "ClippingType.hpp"

// For debugging, uncomment the following define
#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif

/* ============================================================================================= */
MyIGS::MyIGS() :
/* ============================================================================================= */
    m_objectsView(Gtk::manage(new ObjectsTreeView())),
    m_canvas(Gtk::manage(new Canvas())),
    m_scaleAdjustment(Gtk::Adjustment::create(1.0, 0.25, 5.0, 0.25)),
    m_angleXEntry(Gtk::manage(new Gtk::Entry())),
    m_angleYEntry(Gtk::manage(new Gtk::Entry())),
    m_angleZEntry(Gtk::manage(new Gtk::Entry())),
    m_csActive(true),
    m_lbActive(false),
    m_nlnActive(false),
    m_shActive(true),
    m_waActive(false)
{
    m_controller = new InterfaceController(this, m_canvas);
    m_objectsView->setInterfaceController(m_controller);

    // Main window
    set_title("My IGS");
    set_border_width(5);
    set_resizable(false);
    Gtk::VBox * const mainBox = Gtk::manage(new Gtk::VBox());

    // Main widgets
    Gtk::HBox  * const framesBox = Gtk::manage(new Gtk::HBox());
    Gtk::Frame * const controlFrame = Gtk::manage(new Gtk::Frame("Window control"));
    Gtk::Frame * const viewportFrame = Gtk::manage(new Gtk::Frame("Viewport"));
    Gtk::Frame * const objectsFrame = Gtk::manage(new Gtk::Frame("Objects"));

    controlFrame->set_size_request(150,-1);
    objectsFrame->set_size_request(175,-1);

    controlFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    viewportFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    objectsFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

// --------------------------------------------------------------------------------------------- //
// ---------------------------------------- Menubar -------------------------------------------- //

    // File menu
    Gtk::MenuItem * const fileItem = Gtk::manage(new Gtk::MenuItem("File"));
    Gtk::Menu * const fileMenu = Gtk::manage(new Gtk::Menu());
    fileItem->set_submenu(*fileMenu);

    Gtk::MenuItem * const loadItem = Gtk::manage(new Gtk::MenuItem("Load OBJ file"));
    Gtk::MenuItem * const xportItem = Gtk::manage(new Gtk::MenuItem("Export OBJ file"));
    Gtk::MenuItem * const quitItem = Gtk::manage(new Gtk::MenuItem("Quit"));

    fileMenu->append(*loadItem);
    fileMenu->append(*xportItem);
    fileMenu->append(*quitItem);

    loadItem->signal_activate().connect(sigc::mem_fun(*this, &MyIGS::on_action_file_import_obj_file));
    xportItem->signal_activate().connect(sigc::mem_fun(*this, &MyIGS::on_action_file_export_obj_file));
    quitItem->signal_activate().connect(sigc::mem_fun(*this, &MyIGS::on_action_file_quit));

    // Window menu
    Gtk::MenuItem * const windowItem = Gtk::manage(new Gtk::MenuItem("Window"));
    Gtk::Menu * const windowMenu = Gtk::manage(new Gtk::Menu());

    // Window menu > Clipping
    Gtk::MenuItem * const clippingItem = Gtk::manage(new Gtk::MenuItem("Clipping"));
    Gtk::Menu * const clippingMenu = Gtk::manage(new Gtk::Menu());
    windowItem->set_submenu(*windowMenu);
    windowMenu->append(*clippingItem);
    clippingItem->set_submenu(*clippingMenu);

    Gtk::RadioMenuItem::Group line_group;
    Gtk::RadioMenuItem *radioMenuItem = Gtk::manage(new Gtk::RadioMenuItem(line_group, "Cohen-Sutherland"));
    clippingMenu->append(*radioMenuItem);
    radioMenuItem->signal_toggled().connect((sigc::mem_fun(*this, &MyIGS::on_cs_radio_toggled)));
    radioMenuItem->set_active();

    line_group = radioMenuItem->get_group();
    radioMenuItem = Gtk::manage(new Gtk::RadioMenuItem(line_group, "Liang-Barsky"));
    clippingMenu->append(*radioMenuItem);
    radioMenuItem->signal_toggled().connect((sigc::mem_fun(*this, &MyIGS::on_lb_radio_toggled)));

    line_group = radioMenuItem->get_group();
    radioMenuItem = Gtk::manage(new Gtk::RadioMenuItem(line_group, "Nicholl-Lee-Nicholl"));
    Gtk::SeparatorMenuItem *radio_separator = Gtk::manage(new Gtk::SeparatorMenuItem());
    clippingMenu->append(*radioMenuItem);
    clippingMenu->append(*radio_separator);
    radioMenuItem->signal_toggled().connect((sigc::mem_fun(*this, &MyIGS::on_nln_radio_toggled)));
    radioMenuItem->set_sensitive(false);

    Gtk::RadioMenuItem::Group wf_group;
    radioMenuItem = Gtk::manage(new Gtk::RadioMenuItem(wf_group, "Sutherland-Hodgeman"));
    clippingMenu->append(*radioMenuItem);
    radioMenuItem->signal_toggled().connect((sigc::mem_fun(*this, &MyIGS::on_sh_radio_toggled)));
    radioMenuItem->set_active();

    wf_group = radioMenuItem->get_group();
    radioMenuItem = Gtk::manage(new Gtk::RadioMenuItem(wf_group, "Weiler-Atherton"));
    clippingMenu->append(*radioMenuItem);
    radioMenuItem->signal_toggled().connect((sigc::mem_fun(*this, &MyIGS::on_wa_radio_toggled)));
    radioMenuItem->set_sensitive(false);


    // -------------------------
    Gtk::MenuBar * const menuBar = Gtk::manage(new Gtk::MenuBar());
    menuBar->append(*fileItem);
    menuBar->append(*windowItem);
    mainBox->pack_start(*menuBar, Gtk::PACK_SHRINK, 10);


// --------------------------------------------------------------------------------------------- //
// ------------------------------------- Control Frame ----------------------------------------- //

    Gtk::VBox * const controlBox = Gtk::manage(new Gtk::VBox());
    Gtk::Frame * const moveFrame = Gtk::manage(new Gtk::Frame("Translation"));
    Gtk::Frame * const scaleFrame = Gtk::manage(new Gtk::Frame("Scaling"));
    Gtk::Frame * const rotateFrame = Gtk::manage(new Gtk::Frame("Rotation"));

    controlBox->pack_start(*moveFrame, Gtk::PACK_SHRINK, 1);
    controlBox->pack_start(*scaleFrame, Gtk::PACK_SHRINK, 1);
    controlBox->pack_start(*rotateFrame, Gtk::PACK_SHRINK, 1);

    // Scale
    m_scaleAdjustment->signal_value_changed().connect(sigc::mem_fun(*this,
            &MyIGS::on_window_adjustment_value_changed));
    Gtk::Scale * const windowScale = Gtk::manage(new Gtk::Scale(m_scaleAdjustment));
    windowScale->set_digits(1);
    windowScale->set_value_pos(Gtk::POS_BOTTOM);
    windowScale->set_draw_value();

    Gtk::HBox * const scaleBox = Gtk::manage(new Gtk::HBox());
    scaleBox->set_border_width(5);
    scaleBox->pack_start(*windowScale);

    // Scaling frame
    scaleFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    scaleFrame->set_border_width(5);
    scaleFrame->add(*scaleBox);

    // Translation buttons
    Gtk::Button * const moveUpButton = Gtk::manage(new Gtk::Button("Up"));
    Gtk::Button * const moveRightButton = Gtk::manage(new Gtk::Button("Right"));
    Gtk::Button * const moveDownButton = Gtk::manage(new Gtk::Button("Down"));
    Gtk::Button * const moveLeftButton = Gtk::manage(new Gtk::Button("Left"));

    // Translation buttons signals
    moveUpButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::move_window_up));
    moveRightButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::move_window_right));
    moveDownButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::move_window_down));
    moveLeftButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::move_window_left));

    Gtk::Grid * const moveGrid = Gtk::manage(new Gtk::Grid());
    moveGrid->attach(*moveUpButton,2,1,1,1);
    moveGrid->attach(*moveRightButton,3,2,1,1);
    moveGrid->attach(*moveDownButton,2,3,1,1);
    moveGrid->attach(*moveLeftButton,1,2,1,1);
    moveGrid->set_row_homogeneous(true);
    moveGrid->set_column_homogeneous(true);
    moveGrid->set_border_width(5);
    
    // Translation frame
    moveFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    moveFrame->set_border_width(5);
    moveFrame->add(*moveGrid);

    // Rotation frame
    Gtk::HBox * const outerRotationBox = Gtk::manage(new Gtk::HBox());
    Gtk::VBox * const rotEntriesBox = Gtk::manage(new Gtk::VBox());
    Gtk::HBox * const rotEntryXBox = Gtk::manage(new Gtk::HBox());
    Gtk::HBox * const rotEntryYBox = Gtk::manage(new Gtk::HBox());
    Gtk::HBox * const rotEntryZBox = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const angleXLabel = Gtk::manage(new Gtk::Label("About X:"));
    Gtk::Label * const angleYLabel = Gtk::manage(new Gtk::Label("About Y:"));
    Gtk::Label * const angleZLabel = Gtk::manage(new Gtk::Label("About Z:"));
    Gtk::Button * const rotationButton = Gtk::manage(new Gtk::Button());

    m_angleXEntry->set_width_chars(7);
    m_angleYEntry->set_width_chars(7);
    m_angleZEntry->set_width_chars(7);

    rotationButton->set_image_from_icon_name("object-rotate-left");
    rotationButton->set_always_show_image();
    rotationButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::rotate_window));

    rotEntryXBox->pack_start(*angleXLabel, Gtk::PACK_SHRINK, 2);
    rotEntryXBox->pack_start(*m_angleXEntry, Gtk::PACK_SHRINK, 2);
    rotEntryYBox->pack_start(*angleYLabel, Gtk::PACK_SHRINK, 2);
    rotEntryYBox->pack_start(*m_angleYEntry, Gtk::PACK_SHRINK, 2);
    rotEntryZBox->pack_start(*angleZLabel, Gtk::PACK_SHRINK, 2);
    rotEntryZBox->pack_start(*m_angleZEntry, Gtk::PACK_SHRINK, 2);

    rotEntriesBox->pack_start(*rotEntryXBox, Gtk::PACK_SHRINK, 2);
    rotEntriesBox->pack_start(*rotEntryYBox, Gtk::PACK_SHRINK, 2);
    rotEntriesBox->pack_start(*rotEntryZBox, Gtk::PACK_SHRINK, 2);

    outerRotationBox->pack_start(*rotEntriesBox, Gtk::PACK_SHRINK, 2);
    outerRotationBox->pack_start(*rotationButton, Gtk::PACK_SHRINK, 2);
    outerRotationBox->set_border_width(5);

    rotateFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    rotateFrame->set_border_width(5);
    rotateFrame->add(*outerRotationBox);

    controlFrame->add(*controlBox);

// --------------------------------------------------------------------------------------------- //
// ------------------------------------ Viewport Frame ----------------------------------------- //

    Gtk::HBox * const canvasBox = Gtk::manage(new Gtk::HBox());
    Gtk::VBox * const viewportBox = Gtk::manage(new Gtk::VBox());
    canvasBox->set_border_width(10);
    canvasBox->pack_start(*m_canvas, Gtk::PACK_EXPAND_WIDGET, 0);

    viewportBox->pack_start(*canvasBox, Gtk::PACK_EXPAND_WIDGET, 0);
    viewportFrame->add(*viewportBox);

// --------------------------------------------------------------------------------------------- //
// ------------------------------------- Objects Frame ----------------------------------------- //

    // New objects buttons
    Gtk::Button * const createPointButton = Gtk::manage(new Gtk::Button("Point"));
    Gtk::Button * const createLineButton = Gtk::manage(new Gtk::Button("Line"));
    Gtk::Button * const createWireframeButton = Gtk::manage(new Gtk::Button("Wireframe"));
    Gtk::Button * const createBezierButton = Gtk::manage(new Gtk::Button("2D Curve"));

    createPointButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_point));
    createLineButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_line));
    createWireframeButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_wireframe));
    createBezierButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_curve2d));

    Gtk::VBox * const objectsBox = Gtk::manage(new Gtk::VBox());
    Gtk::Label * const labelCreateObjects = Gtk::manage(new Gtk::Label("Create a new object:"));
    Gtk::Separator * const objectsSeparator = Gtk::manage(new Gtk::Separator());
    Gtk::ScrolledWindow * const objectsWindow = Gtk::manage(new Gtk::ScrolledWindow());

    objectsBox->pack_start(*labelCreateObjects, Gtk::PACK_SHRINK, 3);
    objectsBox->pack_start(*createPointButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*createLineButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*createWireframeButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*createBezierButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*objectsSeparator, Gtk::PACK_SHRINK, 3);
    objectsBox->pack_start(*objectsWindow, Gtk::PACK_EXPAND_WIDGET, 0);

    objectsWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    objectsWindow->add(*m_objectsView);
    objectsFrame->add(*objectsBox);

    framesBox->pack_start(*controlFrame, Gtk::PACK_SHRINK, 1);
    framesBox->pack_start(*viewportFrame, Gtk::PACK_EXPAND_WIDGET, 1);
    framesBox->pack_start(*objectsFrame, Gtk::PACK_EXPAND_WIDGET, 1);
    mainBox->pack_start(*framesBox, Gtk::PACK_SHRINK, 0);

    add(*mainBox);
    show_all_children();
}

/* ============================================================================================= */
MyIGS::~MyIGS()
/* ============================================================================================= */
{
    delete m_controller;
}

/* ============================================================================================= */
void MyIGS::on_window_adjustment_value_changed()
/* ============================================================================================= */
{
    m_controller->scale_window(m_scaleAdjustment->get_value());
}

/* ============================================================================================= */
void MyIGS::move_window_up()
/* ============================================================================================= */
{
    m_controller->translate_window(0,1,0);
}

/* ============================================================================================= */
void MyIGS::move_window_right()
/* ============================================================================================= */
{
    m_controller->translate_window(1,0,0);
}

/* ============================================================================================= */
void MyIGS::move_window_down()
/* ============================================================================================= */
{
    m_controller->translate_window(0,-1,0);
}

/* ============================================================================================= */
void MyIGS::move_window_left()
/* ============================================================================================= */
{
    m_controller->translate_window(-1,0,0);
}

/* ============================================================================================= */
void MyIGS::move_window_back()
/* ============================================================================================= */
{
    m_controller->translate_window(0,0,-1);
}

/* ============================================================================================= */
void MyIGS::move_window_forth()
/* ============================================================================================= */
{
    m_controller->translate_window(0,0,1);
}

/* ============================================================================================= */
void MyIGS::rotate_window()
/* ============================================================================================= */
{
    double angle_x = 0.0;
    double angle_y = 0.0;
    double angle_z = 0.0;
    std::stringstream ss_x, ss_y, ss_z;
    ss_x << m_angleXEntry->get_text().raw();
    ss_y << m_angleYEntry->get_text().raw();
    ss_z << m_angleZEntry->get_text().raw();

    if (ss_x.str().size() != 0) {
        ss_x >> angle_x;
    }
    if (ss_y.str().size() != 0) {
        ss_y >> angle_y;
    }
    if (ss_z.str().size() != 0) {
        ss_z >> angle_z;
    }
    if (angle_x != 0.0 || angle_y != 0.0 || angle_z != 0.0) {
        m_controller->rotate_window(Coord<double>(-angle_x, -angle_y, -angle_z));
    }
}

/* ============================================================================================= */
void MyIGS::create_point()
/* ============================================================================================= */
{
    DEBUG_MSG("Creating point...");
    CreatePointDialog dialog("Create a new point");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->create_shape(ShapeType::POINT);
    }
}

/* ============================================================================================= */
void MyIGS::create_line()
/* ============================================================================================= */
{
    DEBUG_MSG("Creating line...");
    CreateLineDialog dialog("Create a new line");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->create_shape(ShapeType::LINE);
    }
}

/* ============================================================================================= */
void MyIGS::create_wireframe()
/* ============================================================================================= */
{
    DEBUG_MSG("Creating wireframe...");
    CreateWireframeDialog dialog("Create a new wireframe");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK && dialog.minimum_vertices()) {
       m_controller->create_shape(ShapeType::WIREFRAME);
    }
}

/* ============================================================================================= */
void MyIGS::create_curve2d()
/* ============================================================================================= */
{
    DEBUG_MSG("Creating 2D curve...");
    CreateCurveDialog dialog("Create a new 2D curve");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK && dialog.minimum_vertices()) {
       m_controller->create_shape(dialog.selected_curve_type());
    }
}

/* ============================================================================================= */
void MyIGS::append_object(const Glib::ustring obj)
/* ============================================================================================= */
{
    m_objectsView->append_object(obj);
}


// --------------------------------------------------------------------------------------------- //
// -------------------------------- Menu Action handlers --------------------------------------- //

/* ============================================================================================= */
void MyIGS::on_action_file_import_obj_file()
/* ============================================================================================= */
{
    if (MyIGS::import_obj_dialog()) {
        const std::string &status_msg = m_controller->get_status_msg();
        Gtk::MessageDialog status_dialog(status_msg, false, Gtk::MessageType::MESSAGE_INFO,
                Gtk::ButtonsType::BUTTONS_OK, true);
        status_dialog.run();
        m_canvas->invalidate();
    }
}

/* ============================================================================================= */
bool MyIGS::import_obj_dialog()
/* ============================================================================================= */
{
    bool import_successful = false;
    
    // Create the dialog
    Gtk::FileChooserDialog dialog("Choose a Wavefront file to be loaded.",
            Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialog.set_transient_for(*this);
    dialog.set_select_multiple(true);

    // Response buttons
    dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);
    dialog.add_button("_Open", Gtk::RESPONSE_OK);

    // Filters
    auto obj_filter = Gtk::FileFilter::create();
    obj_filter->set_name("OBJ files");
    obj_filter->add_pattern("*.obj");
    dialog.add_filter(obj_filter);

    int response = dialog.run();
    switch (response) {
        case (Gtk::RESPONSE_CANCEL):
        {
            DEBUG_MSG("User has cancelled the operation.");
            break;
        }
        case (Gtk::RESPONSE_OK):
        {
            std::vector<std::string> filenames = dialog.get_filenames();
            import_successful = m_controller->import_obj_files(filenames);
            break;
        }
        case (Gtk::RESPONSE_DELETE_EVENT):
        {
            DEBUG_MSG("User has shut the window.");
            break;
        }
        default:
        {
            DEBUG_MSG("User has clicked on a mysterious button...");
            break;
        }
    }
    return import_successful;
}

/* ============================================================================================= */
void MyIGS::on_action_file_export_obj_file()
/* ============================================================================================= */
{
    m_controller->export_obj_file();
}

/* ============================================================================================= */
void MyIGS::on_action_file_quit()
/* ============================================================================================= */
{
    hide(); //Closes the main window to stop the app->run().
}

/* ============================================================================================= */
void MyIGS::on_cs_radio_toggled()
/* ============================================================================================= */
{
    DEBUG_MSG("CS radio toggled!");
    m_csActive ^= true;
    if (m_csActive) {
        m_controller->set_line_clipping_method(LineClipping::CS);
    }
}

/* ============================================================================================= */
void MyIGS::on_lb_radio_toggled()
/* ============================================================================================= */
{
    DEBUG_MSG("LB radio toggled!");
    m_lbActive ^= true;
    if (m_lbActive) {
        m_controller->set_line_clipping_method(LineClipping::LB);
    }
}

/* ============================================================================================= */
void MyIGS::on_nln_radio_toggled()
/* ============================================================================================= */
{
    DEBUG_MSG("NLN radio toggled!");
    m_nlnActive ^= true;
    if (m_nlnActive) {
        m_controller->set_line_clipping_method(LineClipping::NLN);
    }
}

/* ============================================================================================= */
void MyIGS::on_sh_radio_toggled()
/* ============================================================================================= */
{
    DEBUG_MSG("SH radio toggled!");
    m_shActive ^= true;
    if (m_shActive) {
        m_controller->set_polygon_clipping_method(PolygonClipping::SH);
    }
}

/* ============================================================================================= */
void MyIGS::on_wa_radio_toggled()
/* ============================================================================================= */
{
    DEBUG_MSG("WA radio toggled!");
    m_waActive ^= true;
    if (m_waActive) {
        m_controller->set_polygon_clipping_method(PolygonClipping::WA);
    }
}