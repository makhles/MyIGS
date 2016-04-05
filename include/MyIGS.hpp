/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
#include <gtkmm/selectiondata.h>
#include "Canvas.hpp"
#include "OutputBoard.hpp"

class InterfaceController;
class Shape;
class ObjectListView;

class MyIGS : public Gtk::Window {
protected:
    //Gtk::ListViewText * const m_objectsListView;
    ObjectListView * const m_objectsListView;
    OutputBoard * const m_board;
    Canvas * const m_canvas;
    InterfaceController * m_controller;
    Glib::RefPtr<Gtk::TreeSelection> m_selection; 

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
    //void on_selection_changed();
};

#endif  // MYIGS_H