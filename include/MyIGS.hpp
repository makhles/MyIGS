/* MyIGS.h */

#ifndef MYIGS_H
#define MYIGS_H

#include <gtkmm.h>
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
    Gtk::Entry * const m_angleEntry;

    // Menu items
    Gtk::MenuItem * const m_loadItem;
    Gtk::MenuItem * const m_xportItem;
    Gtk::MenuItem * const m_quitItem;

    InterfaceController * m_controller;

    // Control
    void on_window_adjustment_value_changed();
    void move_window_up();
    void move_window_right();
    void move_window_down();
    void move_window_left();
    void rotate_window();

    // Objects creation
    void create_point();
    void create_line();
    void create_wireframe();

    // Action handlers
    void on_action_file_load_obj_file();
    void on_action_file_save_obj_file();
    void on_action_file_quit();

public:
    MyIGS();
    virtual ~MyIGS();
    void append_object(const Glib::ustring obj);
};

#endif  // MYIGS_H