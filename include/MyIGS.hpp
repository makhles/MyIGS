/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include <gtkmm/selectiondata.h>
#include "Canvas.hpp"
#include "OutputBoard.hpp"

class InterfaceController;
class Shape;
class ObjectsTreeView;

class MyIGS : public Gtk::Window {
protected:
    ObjectsTreeView * const m_objectsView;
    OutputBoard * const m_board;
    Canvas * const m_canvas;
    InterfaceController * m_controller;

    // Control
    void zoomWindowIn();
    void zoomWindowOut();
    void moveWindowUp();
    void moveWindowRight();
    void moveWindowDown();
    void moveWindowLeft();

    // Objects creation
    void createPoint();
    void createLine();
    void createWireframe();

public:
    MyIGS();
    virtual ~MyIGS();
    void appendObject(const Glib::ustring obj);
};

#endif  // MYIGS_H