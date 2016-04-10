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
    Glib::RefPtr<Gtk::Adjustment> m_scaleAdjustment;

    InterfaceController * m_controller;

    // Control
    void on_window_adjustment_value_changed();
    void move_window_up();
    void move_window_right();
    void move_window_down();
    void move_window_left();

    // Objects creation
    void create_point();
    void create_line();
    void create_wireframe();

public:
    MyIGS();
    virtual ~MyIGS();
    void append_object(const Glib::ustring obj);
};

#endif  // MYIGS_H