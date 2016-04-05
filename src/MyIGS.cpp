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
    m_canvas(Gtk::manage(new Canvas()))
{
    m_controller = new InterfaceController(this, m_canvas);

    // Main window
    set_title("My IGS");
    set_border_width(10);
    set_resizable(false);

    // Main widgets
    Gtk::HBox  * const mainBox = Gtk::manage(new Gtk::HBox());
    Gtk::Frame * const controlFrame = Gtk::manage(new Gtk::Frame("Control"));
    Gtk::Frame * const viewportFrame = Gtk::manage(new Gtk::Frame("Viewport"));
    Gtk::Frame * const objectsFrame = Gtk::manage(new Gtk::Frame("Objects"));

    controlFrame->set_size_request(150,-1);
    objectsFrame->set_size_request(175,-1);

    controlFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    viewportFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    objectsFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

// --------------------------------------------------------------------------------------------- //
// ---------------------------------------- Zoom Frame ----------------------------------------- //

    Gtk::VBox * const controlBox = Gtk::manage(new Gtk::VBox());
    Gtk::Frame * const scaleFrame = Gtk::manage(new Gtk::Frame("Scaling"));
    Gtk::Frame * const translateFrame = Gtk::manage(new Gtk::Frame("Translation"));
    Gtk::HBox * const scaleBox = Gtk::manage(new Gtk::HBox());
    Gtk::Grid * const scaleGrid = Gtk::manage(new Gtk::Grid());

    controlBox->pack_start(*scaleFrame, Gtk::PACK_SHRINK, 1);
    controlBox->pack_start(*translateFrame, Gtk::PACK_SHRINK, 1);

    // Scaling frame
    scaleFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    scaleFrame->set_border_width(5);
    scaleFrame->add(*scaleBox);

    // Translation frame
    translateFrame->set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    translateFrame->set_border_width(5);
    translateFrame->add(*scaleGrid);

    // Scale buttons
    Gtk::Button * const scaleOutButton = Gtk::manage(new Gtk::Button("Out"));
    Gtk::Button * const scaleInButton = Gtk::manage(new Gtk::Button("In"));

    // Scale buttons signals
    scaleOutButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::zoomWindowOut));
    scaleInButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::zoomWindowIn));

    scaleBox->pack_start(*scaleOutButton, Gtk::PACK_EXPAND_WIDGET, 1);
    scaleBox->pack_start(*scaleInButton, Gtk::PACK_EXPAND_WIDGET, 1);

    // Translation buttons
    Gtk::Button * const moveUpButton = Gtk::manage(new Gtk::Button("Up"));
    Gtk::Button * const moveRightButton = Gtk::manage(new Gtk::Button("Right"));
    Gtk::Button * const moveDownButton = Gtk::manage(new Gtk::Button("Down"));
    Gtk::Button * const moveLeftButton = Gtk::manage(new Gtk::Button("Left"));

    // Translation buttons signals
    moveUpButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowUp));
    moveRightButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowRight));
    moveDownButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowDown));
    moveLeftButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowLeft));

    scaleGrid->attach(*moveUpButton,2,1,1,1);
    scaleGrid->attach(*moveRightButton,3,2,1,1);
    scaleGrid->attach(*moveDownButton,2,3,1,1);
    scaleGrid->attach(*moveLeftButton,1,2,1,1);
    
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

    createPointButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createPoint));
    createLineButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createLine));
    createWireframeButton->signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createWireframe));

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


void MyIGS::zoomWindowIn() {
    m_controller->zoomWindow(1);
}


void MyIGS::zoomWindowOut() {
    m_controller->zoomWindow(-1);
}


void MyIGS::moveWindowUp() {
    m_controller->moveWindow(0,1);
}


void MyIGS::moveWindowRight() {
    m_controller->moveWindow(1,0);
}


void MyIGS::moveWindowDown() {
    m_controller->moveWindow(0,-1);
}


void MyIGS::moveWindowLeft() {
    m_controller->moveWindow(-1,0);
}


void MyIGS::createPoint() {
    std::cout << "Creating point..." << std::endl;
    CreatePointDialog dialog("Create a new point");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->createShape(ShapeType::POINT);
    }
}


void MyIGS::createLine() {
    std::cout << "Creating line..." << std::endl;
    CreateLineDialog dialog("Create a new line");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       m_controller->createShape(ShapeType::LINE);
    }
}


void MyIGS::createWireframe() {
    std::cout << "Creating wireframe..." << std::endl;
    CreateWireframeDialog dialog("Create a new wireframe");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK && dialog.buildWireframe()) {
       m_controller->createShape(ShapeType::WIREFRAME);
    }
}


void MyIGS::appendObject(const Glib::ustring obj) {
    m_objectsView->appendObject(obj);
}