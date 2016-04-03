/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include "Canvas.hpp"
#include "OutputBoard.hpp"

class InterfaceController;
class Shape;

class MyIGS : public Gtk::Window {
protected:
    Gtk::ListViewText * const m_objectsListView;
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
    void appendObjectToViewList(const Shape *obj);
};

#endif  // MYIGS_H