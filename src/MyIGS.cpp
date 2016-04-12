/* MyIGS.cpp */

#include <iostream>
#include "MyIGS.hpp"
#include "InterfaceController.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "CreatePointDialog.hpp"
#include "CreateLineDialog.hpp"
#include "CreateWireframeDialog.hpp"
#include "ObjectsTreeView.hpp"

MyIGS::MyIGS() :
    m_objectsView(Gtk::manage(new ObjectsTreeView())),
    m_board(Gtk::manage(new OutputBoard())),
    m_canvas(Gtk::manage(new Canvas())),
    m_scaleAdjustment(Gtk::Adjustment::create(1.0, 0.25, 5.0, 0.25)),
    m_angleEntry(Gtk::manage(new Gtk::Entry()))
{
    m_controller = new InterfaceController(this, m_canvas);
    m_objectsView->setInterfaceController(m_controller);

    // Main window
    set_title("My IGS");
    set_border_width(10);
    set_resizable(false);

    // Main widgets
    Gtk::HBox  * const mainBox = Gtk::manage(new Gtk::HBox());
    Gtk::Frame * const controlFrame = Gtk::manage(new Gtk::Frame("Window control"));
    Gtk::Frame * const viewportFrame = Gtk::manage(new Gtk::Frame("Viewport"));
    Gtk::Frame * const objectsFrame = Gtk::manage(new Gtk::Frame("Objects"));

    controlFrame->set_size_request(150,-1);
    objectsFrame->set_size_request(175,-1);

    controlFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    viewportFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    objectsFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

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
    windowScale->set_digits(2);
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
    Gtk::HBox * const rotationBox = Gtk::manage(new Gtk::HBox());
    Gtk::Label * const angleLabel = Gtk::manage(new Gtk::Label("Angle:"));
    Gtk::Button * const rotationButton = Gtk::manage(new Gtk::Button());

    m_angleEntry->set_width_chars(6);

    rotationButton->set_image_from_icon_name("object-rotate-left");
    rotationButton->set_always_show_image();
    rotationButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::rotate_window));

    rotationBox->pack_start(*angleLabel, Gtk::PACK_SHRINK, 2);
    rotationBox->pack_start(*m_angleEntry, Gtk::PACK_SHRINK, 2);
    rotationBox->pack_start(*rotationButton, Gtk::PACK_SHRINK, 2);
    rotationBox->set_border_width(5);

    rotateFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    rotateFrame->set_border_width(5);
    rotateFrame->add(*rotationBox);

    controlFrame->add(*controlBox);

// --------------------------------------------------------------------------------------------- //
// ------------------------------------ Viewport Frame ----------------------------------------- //

    Gtk::VBox * const viewportBox = Gtk::manage(new Gtk::VBox());
    viewportBox->pack_start(*m_canvas, Gtk::PACK_EXPAND_WIDGET, 1);
    viewportBox->pack_start(*m_board, Gtk::PACK_EXPAND_WIDGET, 1);
    viewportFrame->add(*viewportBox);

// --------------------------------------------------------------------------------------------- //
// ------------------------------------- Objects Frame ----------------------------------------- //

    // New objects buttons
    Gtk::Button * const createPointButton = Gtk::manage(new Gtk::Button("Point"));
    Gtk::Button * const createLineButton = Gtk::manage(new Gtk::Button("Line"));
    Gtk::Button * const createWireframeButton = Gtk::manage(new Gtk::Button("Wireframe"));

    createPointButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_point));
    createLineButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_line));
    createWireframeButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::create_wireframe));

    Gtk::VBox * const objectsBox = Gtk::manage(new Gtk::VBox());
    Gtk::Label * const labelCreateObjects = Gtk::manage(new Gtk::Label("Create a new object:"));
    Gtk::Separator * const objectsSeparator = Gtk::manage(new Gtk::Separator());
    Gtk::ScrolledWindow * const objectsWindow = Gtk::manage(new Gtk::ScrolledWindow());

    objectsBox->pack_start(*labelCreateObjects, Gtk::PACK_SHRINK, 3);
    objectsBox->pack_start(*createPointButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*createLineButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*createWireframeButton, Gtk::PACK_SHRINK, 0);
    objectsBox->pack_start(*objectsSeparator, Gtk::PACK_SHRINK, 3);
    objectsBox->pack_start(*objectsWindow, Gtk::PACK_EXPAND_WIDGET, 0);

    objectsWindow->set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    objectsWindow->add(*m_objectsView);
    objectsFrame->add(*objectsBox);

    mainBox->pack_start(*controlFrame, Gtk::PACK_SHRINK, 1);
    mainBox->pack_start(*viewportFrame, Gtk::PACK_EXPAND_WIDGET, 1);
    mainBox->pack_start(*objectsFrame, Gtk::PACK_EXPAND_WIDGET, 1);

    add(*mainBox);
    show_all_children();
}


MyIGS::~MyIGS() {
    delete m_controller;
}


void MyIGS::on_window_adjustment_value_changed() {
    m_controller->scale_window(m_scaleAdjustment->get_value());
}


void MyIGS::move_window_up() {
    m_controller->move_window(0,1);
}


void MyIGS::move_window_right() {
    m_controller->move_window(1,0);
}


void MyIGS::move_window_down() {
    m_controller->move_window(0,-1);
}


void MyIGS::move_window_left() {
    m_controller->move_window(-1,0);
}


void MyIGS::rotate_window() {
    double angle;
    std::stringstream angle_stream;
    angle_stream << m_angleEntry->get_text().raw();

    if (angle_stream.str().size() != 0) {
        angle_stream >> angle;
        if (angle != 0.0) {
            m_controller->rotate_window(angle);
        }
    }
}


void MyIGS::create_point() {
    std::cout << "Creating point..." << std::endl;
    CreatePointDialog dialog("Create a new point");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->create_shape(ShapeType::POINT);
    }
}


void MyIGS::create_line() {
    std::cout << "Creating line..." << std::endl;
    CreateLineDialog dialog("Create a new line");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->create_shape(ShapeType::LINE);
    }
}


void MyIGS::create_wireframe() {
    std::cout << "Creating wireframe..." << std::endl;
    CreateWireframeDialog dialog("Create a new wireframe");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK && dialog.build_wireframe()) {
       m_controller->create_shape(ShapeType::WIREFRAME);
    }
}


void MyIGS::append_object(const Glib::ustring obj) {
    m_objectsView->append_object(obj);
}