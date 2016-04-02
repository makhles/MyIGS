/* MyIGS.cpp */

#include <iostream>
#include "MyIGS.hpp"
#include "InterfaceController.hpp"
#include "Shape.hpp"
#include "ShapeType.hpp"
#include "CreatePointDialog.hpp"
#include "CreateLineDialog.hpp"
#include "CreateWireframeDialog.hpp"

MyIGS::MyIGS() :
        m_mainBox(Gtk::manage(new Gtk::HBox())),
        _zoomButtonOut("Out"),
        _zoomButtonIn("In"),
        _dispButtonUp("Up"),
        _dispButtonDown("Down"),
        _dispButtonLeft("Left"),
        _dispButtonRight("Right"),
        _buttonCreatePoint("Point"),
        _buttonCreateLine("Line"),
        _buttonCreateWireframe("Wireframe"),
        _labelCreateObjects("Create a new object:"),
        _objectsListView(1) {

    /* Add views to the controller */
    _interfaceController = new InterfaceController(this, &_canvas);

    /* Main window */
    set_title("My IGS");
    set_border_width(10);
    set_resizable(false);

    /* Frames */
    MyIGS::createControlFrame();
    MyIGS::createViewportFrame();
    MyIGS::createObjectsFrame();

    add(*m_mainBox);
    show_all_children();
}

MyIGS::~MyIGS() {
    delete _interfaceController;
}

void MyIGS::createControlFrame() {
    _controlBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    _zoomBox.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

    /* Zoom frame */
    _zoomFrame.set_label("Zoom");
    _zoomFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    _zoomFrame.set_border_width(5);
    _zoomFrame.add(_zoomBox);
    _controlBox.pack_start(_zoomFrame, Gtk::PACK_SHRINK, 1);

    /* Zoom frame buttons */
    _zoomButtonOut.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::zoomWindowOut));
    _zoomButtonIn.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::zoomWindowIn));
    _zoomBox.pack_start(_zoomButtonOut, Gtk::PACK_EXPAND_WIDGET, 1);
    _zoomBox.pack_start(_zoomButtonIn, Gtk::PACK_EXPAND_WIDGET, 1);

    /* Displacement Frame */
    _dispFrame.set_label("Displacement");
    _dispFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    _dispFrame.set_border_width(5);
    _controlBox.pack_start(_dispFrame, Gtk::PACK_SHRINK, 1);

    /* Displacement buttons */
    _dispButtonUp.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowUp));
    _dispButtonRight.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowRight));
    _dispButtonDown.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowDown));
    _dispButtonLeft.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::moveWindowLeft));
    _dispGrid.attach(_dispButtonUp,2,1,1,1);
    _dispGrid.attach(_dispButtonRight,3,2,1,1);
    _dispGrid.attach(_dispButtonDown,2,3,1,1);
    _dispGrid.attach(_dispButtonLeft,1,2,1,1);
    _dispFrame.add(_dispGrid);

    _controlFrame.set_label("Control");
    _controlFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    _controlFrame.set_size_request(150,-1);
    _controlFrame.add(_controlBox);

    m_mainBox->pack_start(_controlFrame, Gtk::PACK_SHRINK, 1);
}

void MyIGS::createViewportFrame() {
    _viewportBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    _viewportBox.pack_start(_canvas, Gtk::PACK_EXPAND_WIDGET, 1);
    _viewportBox.pack_start(_board, Gtk::PACK_EXPAND_WIDGET, 1);

    _viewportFrame.set_label("Viewport");
    _viewportFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);

    _viewportFrame.add(_viewportBox);
    m_mainBox->pack_start(_viewportFrame, Gtk::PACK_EXPAND_WIDGET, 1);
}

void MyIGS::createObjectsFrame() {

    /* Objects frame */
    _objectsFrame.set_label("Objects");
    _objectsFrame.set_shadow_type(Gtk::SHADOW_ETCHED_OUT);
    _objectsFrame.set_size_request(175,-1);
    _objectsFrame.add(_objectsBox);

    /* New objects buttons */
    _buttonCreatePoint.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createPoint));
    _buttonCreateLine.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createLine));
    _buttonCreateWireframe.signal_clicked().connect(sigc::mem_fun(*this, &MyIGS::createWireframe));

    /* Pack everything */
    _objectsBox.set_orientation(Gtk::ORIENTATION_VERTICAL);
    _objectsBox.pack_start(_labelCreateObjects, Gtk::PACK_SHRINK, 3);
    _objectsBox.pack_start(_buttonCreatePoint, Gtk::PACK_SHRINK, 0);
    _objectsBox.pack_start(_buttonCreateLine, Gtk::PACK_SHRINK, 0);
    _objectsBox.pack_start(_buttonCreateWireframe, Gtk::PACK_SHRINK, 0);
    _objectsBox.pack_start(_objectsSeparator, Gtk::PACK_SHRINK, 3);
    _objectsBox.pack_start(_objectsWindow, Gtk::PACK_EXPAND_WIDGET, 0);

    /* Objects window */
    _objectsWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);
    _objectsWindow.add(_objectsListView);
    _objectsListView.set_column_title(0, "Current objects:");

    m_mainBox->pack_start(_objectsFrame, Gtk::PACK_EXPAND_WIDGET, 1);
}

void MyIGS::zoomWindowIn() {
    _interfaceController->zoomWindow(1);
}

void MyIGS::zoomWindowOut() {
    _interfaceController->zoomWindow(-1);
}

void MyIGS::moveWindowUp() {
    _interfaceController->moveWindow(0,1);
}

void MyIGS::moveWindowRight() {
    _interfaceController->moveWindow(1,0);
}

void MyIGS::moveWindowDown() {
    _interfaceController->moveWindow(0,-1);
}

void MyIGS::moveWindowLeft() {
    _interfaceController->moveWindow(-1,0);
}

void MyIGS::createPoint() {
    std::cout << "Creating point..." << std::endl;
    CreatePointDialog dialog("Create a new point");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       _interfaceController->createShape(ShapeType::POINT);
    }
}

void MyIGS::createLine() {
    std::cout << "Creating line..." << std::endl;
    CreateLineDialog dialog("Create a new line");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK) {
       _interfaceController->createShape(ShapeType::LINE);
    }
}

void MyIGS::createWireframe() {
    std::cout << "Creating wireframe..." << std::endl;
    CreateWireframeDialog dialog("Create a new wireframe");
    int response = dialog.run();
    if (response == Gtk::RESPONSE_OK && dialog.buildWireframe()) {
       _interfaceController->createShape(ShapeType::WIREFRAME);
    }
}

void MyIGS::appendObjectToViewList(const Shape *obj) {
    _objectsListView.append(obj->get_name());
}